#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <own_drivers.h>

/* ========= Variables Globales ==============*/
/* ---------     Semaforos        ------------*/
extern xSemaphoreHandle sem_state;
extern xSemaphoreHandle sem_eeprom;

/* ---------  Colas de mensaje    ------------*/

/* ---------  Variables de estado ------------*/
extern uint8_t clave_ok;
static GPIO_TypeDef *RC522_CS_GPIO_Port;
static uint16_t RC522_CS_Pin;
static SPI_HandleTypeDef *spi;
/* ===========================================*/


uint8_t rfid_add_id(uint32_t id)
{
	static uint8_t current_index = 0;
	uint8_t wbuff[4];
	uint8_t status = CARD_NOT_ADDED;

	memcpy(wbuff, &id , 4);


	xSemaphoreTake(sem_eeprom,portMAX_DELAY);
	status = eeprom_write_page(RFID_INIT_PAGE, 4*current_index, wbuff, 4);
	xSemaphoreGive(sem_eeprom);

	current_index++;
	current_index %= 2;

	uint8_t valid_id[8];
	xSemaphoreTake(sem_eeprom,portMAX_DELAY);
	eeprom_read_page(RFID_INIT_PAGE, 0, valid_id, 8);
	xSemaphoreGive(sem_eeprom);

	return CARD_ADDED;
}



/*
 * Function Name: rfid_toggle_state
 * Function Description: Funcion que detecta si se acerco una tarjeta y togglea el estado del sistema.
 * Input Parameters:
 * 					None.
 * Return value: None
 */
void rfid_toggle_state(void)
{
	if (rfid_debounce() == CARD_DETECTED)
	{
		// Toggle clave state
		xSemaphoreTake(sem_state,portMAX_DELAY);
		clave_ok = 1;
		xSemaphoreGive(sem_state);
	}
}

/*
 * Function Name: rfid_debounce
 * Function Description: Función que asegura que se haya detectado una tarjeta y evita que se llame multiples veces la misma función.
 * Input Parameters:
 * 					None.
 * Return value:
 *					CARD_NOT_FOUND  if card was not validated nor detected.
 *					CARD_DETECTED 	if card was detected and validated.
 */
uint8_t rfid_debounce(void)
{
	static uint8_t estado = WAITING_CARD;
	static uint32_t initial_time = 0;
	uint8_t return_value = CARD_NOT_FOUND;
	uint32_t current_time = 0;
	uint8_t id[4];	// Not important here

	switch(estado)
	{
		case WAITING_CARD:
			if (rfid_find_card(id) == CARD_DETECTED)
			{
				initial_time = HAL_GetTick();
				estado = VALIDATING_CARD;
			}
			break;

		case VALIDATING_CARD:
			if (rfid_find_card(id) == CARD_NOT_FOUND)
			{
				estado = WAITING_CARD;
			}else{
				current_time = HAL_GetTick();
				if (current_time - initial_time >= DETECTION_TIMEOUT)
				{
					if (rfid_identify_card() == CARD_DETECTED)
					{
						initial_time = 0;
						estado = REMOVING_CARD;
						return_value = CARD_DETECTED;
					}else{
						initial_time = 0;
						estado = REMOVING_CARD;
					}
				}
			}
			break;

		case REMOVING_CARD:
			return_value = CARD_NOT_FOUND;
			if (rfid_find_card(id) == CARD_NOT_FOUND)
			{
				estado = WAITING_CARD;
			}
			break;
	}
	return return_value;
}


/*
 * Function Name: rfid_identify_card
 * Function Description: Función encargada de identificar si la tarjeta fue aceptada.
 * Input Parameters:
 * 					None.
 * Return value:
 *					CARD_NOT_FOUND  if card was not detected.
 *					CARD_DETECTED 	if card was detected.
 */
uint8_t rfid_identify_card(void)
{
	uint8_t status;
	uint8_t id[4];
	uint8_t valid_id[2*4];

	status = rfid_find_card(id);
	if (status == CARD_DETECTED)
	{

		xSemaphoreTake(sem_eeprom,portMAX_DELAY);
		eeprom_read_page(RFID_INIT_PAGE, 0, valid_id, 8);
		xSemaphoreGive(sem_eeprom);

		for (uint8_t n = 0; n < 2; n++)
		{
			if( memcmp(&valid_id[n*4], id, 4) == 0)
				return CARD_DETECTED;
		}
	}

	// Si todavia no se retorno
	return CARD_NOT_FOUND;
}


/*
 * Function Name: rfid_find_card
 * Function Description: Función encargada de detectar tarjetas.
 * Input Parameters:
 * 					None.
 * Return value:
 *					CARD_NOT_FOUND  if card was not detected.
 *					CARD_DETECTED 	if card was detected.
 */
uint8_t rfid_find_card( uint8_t* id)
{
	uint8_t status;
	uint8_t cardstr[MAX_LEN+1];

	status = 0;
	memset(cardstr,0,sizeof(cardstr));
	status = (uint8_t) MFRC522_Request(PICC_REQIDL, cardstr);
	if (status == MI_OK)
	{
		HAL_Delay(2);
		MFRC522_Anticoll(cardstr);
		memcpy(id, &cardstr , 4);
		MFRC522_Halt();
		HAL_Delay(2);
		return CARD_DETECTED;
	}

	// Si todavia no se retorno
	return CARD_NOT_FOUND;
}


/*
 * Function Name: Write_MFRC5200
 * Function Description: To a certain MFRC522 register to write a byte of data
 * Input Parameters:
 * 					addr - register address
 * 					val  - the value to be written
 * Return value: None
 */
void Write_MFRC522(u_char addr, u_char val) {
	u_char addr_bits = ((addr<<1) & 0x7E);

	HAL_GPIO_WritePin(RC522_CS_GPIO_Port, RC522_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(spi, &addr_bits, 1, 500);
	HAL_SPI_Transmit(spi, &val, 1, 500);
	HAL_GPIO_WritePin(RC522_CS_GPIO_Port, RC522_CS_Pin, GPIO_PIN_SET);
}


/*
 * Function Name: Read_MFRC522
 * Description: From a certain MFRC522 read a byte of data register
 * Input Parameters:
 * 					addr - register address
 * Returns: a byte of data read from the
 */
u_char Read_MFRC522(u_char addr) {
    u_char rx_bits;
    u_char addr_bits = (((addr<<1) & 0x7E) | 0x80);

    HAL_GPIO_WritePin(RC522_CS_GPIO_Port, RC522_CS_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(spi, &addr_bits, 1, 500);
    HAL_SPI_Receive(spi, &rx_bits, 1, 500);
    HAL_GPIO_WritePin(RC522_CS_GPIO_Port, RC522_CS_Pin, GPIO_PIN_SET);

	return (u_char) rx_bits; // return the rx bits, casting to an 8 bit int and chopping off the upper 24 bits
}

/*
 * Function Name:SetBitMask
 * Description: Set RC522 register bit
 * Input parameters:
 * 					reg  - register address
 * 					mask - set value
 * Return value: None
 */
void SetBitMask(u_char reg, u_char mask)
{
    u_char tmp;
    tmp = Read_MFRC522(reg);
    Write_MFRC522(reg, tmp | mask);  // set bit mask
}
//
/*
 * Function Name: ClearBitMask
 * Description: clear RC522 register bit
 * Input parameters:
 * 					reg  - register address
 * 					mask - clear bit value
 * Return value: None
*/
void ClearBitMask(u_char reg, u_char mask)
{
    u_char tmp;
    tmp = Read_MFRC522(reg);
    Write_MFRC522(reg, tmp & (~mask));  // clear bit mask
}


/*
 * Function Name: AntennaOn
 * Description: Open antennas, each time you start or shut down the natural barrier between the transmitter should be at least 1ms interval
 * Input: None
 * Return value: None
 */
void AntennaOn(void)
{
	SetBitMask(TxControlReg, 0x03);
}


/*
  * Function Name: AntennaOff
  * Description: Close antennas, each time you start or shut down the natural barrier between the transmitter should be at least 1ms interval
  * Input: None
  * Return value: None
 */
void AntennaOff(void)
{
	ClearBitMask(TxControlReg, 0x03);
}


/*
 * Function Name: ResetMFRC522
 * Description: Reset RC522
 * Input: None
 * Return value: None
 */
void MFRC522_Reset(void)
{
	Write_MFRC522(CommandReg, PCD_RESETPHASE);
}


/*
 * Function Name:InitMFRC522
 * Description: Initialize RC522
 * Input: None
 * Return value: None
*/
void MFRC522_Init(SPI_HandleTypeDef *s, GPIO_TypeDef *g, uint16_t pin)
{
	spi = s;
	RC522_CS_GPIO_Port = g;
	RC522_CS_Pin = pin;

	//  MSS_GPIO_set_output( MSS_GPIO_1, 1 );
    MFRC522_Reset();

    // Timer: TPrescaler*TreloadVal/6.78MHz = 24ms
    Write_MFRC522(TModeReg, 0x80); // 0x8D);      // Tauto=1; f(Timer) = 6.78MHz/TPreScaler
    Write_MFRC522(TPrescalerReg, 0xA9); //0x34); // TModeReg[3..0] + TPrescalerReg
    Write_MFRC522(TReloadRegL, 0x03); //30);
    Write_MFRC522(TReloadRegH, 0xE8); //0);
    Write_MFRC522(TxAutoReg, 0x40);     // force 100% ASK modulation
    Write_MFRC522(ModeReg, 0x3D);       // CRC Initial value 0x6363

    // turn antenna on
    AntennaOn();
}



/*
 * Function Name:MFRC522_Request
 * Description: Find cards, read the card type number
 * Input parameters: reqMode - find cards way
 *   				 TagType - Return Card Type
 *    						0x4400 = Mifare_UltraLight
 *    						0x0400 = Mifare_One(S50)
 *    						0x0200 = Mifare_One(S70)
 *    						0x0800 = Mifare_Pro(X)
 *    						0x4403 = Mifare_DESFire
 * Return value: the successful return MI_OK
 */
u_char MFRC522_Request(u_char reqMode, u_char *TagType)
{
	u_char status;
	uint backBits; // The received data bits

	Write_MFRC522(BitFramingReg, 0x07);   // TxLastBists = BitFramingReg[2..0]

	TagType[0] = reqMode;

	status = MFRC522_ToCard(PCD_TRANSCEIVE, TagType, 1, TagType, &backBits);
	if ((status != MI_OK) || (backBits != 0x10)) {
	status = MI_ERR;
	}

	return status;
}


/*
 * Function Name: MFRC522_ToCard
 * Description: RC522 and ISO14443 card communication
 * Input Parameters:
 * 					command  - MF522 command word,
 *			 		sendData - RC522 sent to the card by the data
 *			 		sendLen  - Length of data sent
 *			 		backData - Received the card returns data,
 *			 		backLen  - Return data bit length
 * Return value: the successful return MI_OK
 */
u_char MFRC522_ToCard(u_char command, u_char *sendData, u_char sendLen, u_char *backData, uint *backLen)
{
	u_char status = MI_ERR;
	u_char irqEn = 0x00;
	u_char waitIRq = 0x00;
	u_char lastBits;
	u_char n;
	uint i;

	switch (command)
	{
	case PCD_AUTHENT:     // Certification cards close
	  {
		irqEn = 0x12;
		waitIRq = 0x10;
		break;
	  }
	case PCD_TRANSCEIVE:  // Transmit FIFO data
	  {
		irqEn = 0x77;
		waitIRq = 0x30;
		break;
	  }
	default:
	  break;
	}

	Write_MFRC522(CommIEnReg, irqEn|0x80);  // Interrupt request
	ClearBitMask(CommIrqReg, 0x80);         // Clear all interrupt request bit
	SetBitMask(FIFOLevelReg, 0x80);         // FlushBuffer=1, FIFO Initialization

	Write_MFRC522(CommandReg, PCD_IDLE);    // NO action; Cancel the current command

	// Writing data to the FIFO
	for (i=0; i<sendLen; i++)
	{
	Write_MFRC522(FIFODataReg, sendData[i]);
	}

	// Execute the command
	Write_MFRC522(CommandReg, command);
	if (command == PCD_TRANSCEIVE)
	{
	SetBitMask(BitFramingReg, 0x80);      // StartSend=1,transmission of data starts
	}

	// Waiting to receive data to complete
	i = 2000;	// i according to the clock frequency adjustment, the operator M1 card maximum waiting time 25ms
	do
	{
	// CommIrqReg[7..0]
	// Set1 TxIRq RxIRq IdleIRq HiAlerIRq LoAlertIRq ErrIRq TimerIRq
	n = Read_MFRC522(CommIrqReg);
	i--;
	}
	while ((i!=0) && !(n&0x01) && !(n&waitIRq));

	ClearBitMask(BitFramingReg, 0x80);      // StartSend=0

	if (i != 0)
	{
		if(!(Read_MFRC522(ErrorReg) & 0x1B))  // BufferOvfl Collerr CRCErr ProtecolErr
		{
		  status = MI_OK;
		  if (n & irqEn & 0x01)
		  {
			status = MI_NOTAGERR;             // ??
		  }

		  if (command == PCD_TRANSCEIVE)
		  {
			n = Read_MFRC522(FIFOLevelReg);
			lastBits = Read_MFRC522(ControlReg) & 0x07;
			if (lastBits)
			{
			  *backLen = (n-1)*8 + lastBits;
			}
			else
			{
			  *backLen = n*8;
			}

			if (n == 0)
			{
			  n = 1;
			}
			if (n > MAX_LEN)
			{
			  n = MAX_LEN;
			}

			// Reading the received data in FIFO
			for (i=0; i<n; i++)
			{
			  backData[i] = Read_MFRC522(FIFODataReg);
			}
		  }
		}
	}

	return status;
}


/*
 * Function Name: MFRC522_Anticoll
 * Description: Anti-collision detection, reading selected card serial number card
 * Input parameters:
 * 					serNum - returns 4 bytes card serial number, the first 5 bytes for the checksum byte
 * Return value: the successful return MI_OK
 */
u_char MFRC522_Anticoll(u_char *serNum)
{
	u_char status;
	u_char i;
	u_char serNumCheck=0;
	uint unLen;

	Write_MFRC522(BitFramingReg, 0x00);		//TxLastBists = BitFramingReg[2..0]
	serNum[0] = PICC_ANTICOLL;
	serNum[1] = 0x20;
	status = MFRC522_ToCard(PCD_TRANSCEIVE, serNum, 2, serNum, &unLen);

	if (status == MI_OK)
	{
		//Check card serial number
		for (i=0; i<4; i++)
		{
		  serNumCheck ^= serNum[i];
		}
		if (serNumCheck != serNum[i])
		{
		  status = MI_ERR;
		}
	}
	return status;
}


/*
 * Function Name: MFRC522_Read
 * Description: Read block data
 * Input parameters:
 * 					blockAddr - block address
 * 					recvData  - read block data
 * Return value: the successful return MI_OK
 */
u_char MFRC522_Read(u_char blockAddr, u_char *recvData)
{
	u_char status;
	uint unLen;

	recvData[0] = PICC_READ;
	recvData[1] = blockAddr;
	CalulateCRC(recvData,2, &recvData[2]);
	status = MFRC522_ToCard(PCD_TRANSCEIVE, recvData, 4, recvData, &unLen);

	if ((status != MI_OK) || (unLen != 0x90))
	{
	status = MI_ERR;
	}

	return status;
}


/*
 * Function Name: MFRC522_Write
 * Description: Write block data
 * Input parameters: blockAddr - block address; writeData - to 16-byte data block write
 * Return value: the successful return MI_OK
 */
u_char MFRC522_Write(u_char blockAddr, u_char *writeData)
{
	u_char status;
	uint recvBits;
	u_char i;
	u_char buff[18];

	buff[0] = PICC_WRITE;
	buff[1] = blockAddr;
	CalulateCRC(buff, 2, &buff[2]);
	status = MFRC522_ToCard(PCD_TRANSCEIVE, buff, 4, buff, &recvBits);

	if ((status != MI_OK))// || (recvBits != 4) || ((buff[0] & 0x0F) != 0x0A))
	{
		status = MI_ERR;
	}

	if (status == MI_OK)
	{
		for (i=0; i<16; i++)		//Data to the FIFO write 16Byte
		{
		  buff[i] = *(writeData+i);
		}
		CalulateCRC(buff, 16, &buff[16]);
		status = MFRC522_ToCard(PCD_TRANSCEIVE, buff, 18, buff, &recvBits);

		if ((status != MI_OK))// || (recvBits != 4) || ((buff[0] & 0x0F) != 0x0A))
		{
		  status = MI_ERR;
		}
	}

	return status;
}


/*
 * Function Name: CalulateCRC
 * Description: CRC calculation with MF522
 * Input parameters:
 * 					pIndata  - To read the CRC data
 * 					len 	 - the data length
 * 					pOutData - CRC calculation results
 * Return value: None
 */
void CalulateCRC(u_char *pIndata, u_char len, u_char *pOutData)
{
	u_char i, n;

	ClearBitMask(DivIrqReg, 0x04);			//CRCIrq = 0
	SetBitMask(FIFOLevelReg, 0x80);			//Clear the FIFO pointer

	//Writing data to the FIFO
	for (i=0; i<len; i++)
	{
		Write_MFRC522(FIFODataReg, *(pIndata+i));
	}
	Write_MFRC522(CommandReg, PCD_CALCCRC);

	//Wait CRC calculation is complete
	i = 0xFF;
	do {
		n = Read_MFRC522(DivIrqReg);
		i--;
	} while ((i!=0) && !(n&0x04));			//CRCIrq = 1

	//Read CRC calculation result
	pOutData[0] = Read_MFRC522(CRCResultRegL);
	pOutData[1] = Read_MFRC522(CRCResultRegM);
}


/*
 * Function Name: MFRC522_Auth
 * Description: Verify card password
 * Input parameters:
 * 					authMode  - Password Authentication Mode
                 	 	 0x60 = A key authentication
                 	 	 0x61 = Authentication Key B
             	 	BlockAddr - Block address
             	 	Sectorkey - Sector password
             	 	serNum	  - Card serial number, 4-byte
 * Return value: the successful return MI_OK
 */
u_char MFRC522_Auth(u_char authMode, u_char BlockAddr, u_char *Sectorkey, u_char *serNum)
{
	u_char status;
	uint recvBits;
	u_char i;
	u_char buff[12];

	//Verify the command block address + sector + password + card serial number
	buff[0] = authMode;
	buff[1] = BlockAddr;
	for (i=0; i<6; i++)
	{
		buff[i+2] = *(Sectorkey+i);
	}
	for (i=0; i<4; i++)
	{
		buff[i+8] = *(serNum+i);
	}
	status = MFRC522_ToCard(PCD_AUTHENT, buff, 12, buff, &recvBits);

	if ((status != MI_OK) || (!(Read_MFRC522(Status2Reg) & 0x08)))
	{
		status = MI_ERR;
	}

	return status;
}


/*
 * Function Name: MFRC522_SelectTag
 * Description: election card, read the card memory capacity
 * Input parameters:
 * 					serNum - Incoming card serial number
 * Return value: the successful return of card capacity
 */
u_char MFRC522_SelectTag(u_char *serNum)
{
	u_char i;
	u_char status;
	u_char size;
	uint recvBits;
	u_char buffer[9];

	//ClearBitMask(Status2Reg, 0x08);			//MFCrypto1On=0

	buffer[0] = PICC_SElECTTAG;
	buffer[1] = 0x70;
	for (i=0; i<5; i++)
	{
	buffer[i+2] = *(serNum+i);
	}
	CalulateCRC(buffer, 7, &buffer[7]);		//??
	status = MFRC522_ToCard(PCD_TRANSCEIVE, buffer, 9, buffer, &recvBits);

	if ((status == MI_OK) && (recvBits == 0x18))
	{
	size = buffer[0];
	}
	else
	{
	size = 0;
	}

	return size;
}


/*
 * Function Name: MFRC522_Halt
 * Description: Command card into hibernation
 * Input: None
 * Return value: None
 */
void MFRC522_Halt(void)
{
	u_char status;
	uint unLen;
	u_char buff[4];

	buff[0] = PICC_HALT;
	buff[1] = 0;
	CalulateCRC(buff, 2, &buff[2]);

	status = MFRC522_ToCard(PCD_TRANSCEIVE, buff, 4, buff,&unLen);
	UNUSED(status);
}


void MFRC522_StopCrypto1(void) {

	ClearBitMask(Status2Reg, 0x08); // Status2Reg[7..0] bits are: TempSensClear I2CForceHS reserved reserved   MFCrypto1On ModemState[2:0]
}