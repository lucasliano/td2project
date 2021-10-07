<!-- Badged -->
[![forthebadge](https://forthebadge.com/images/badges/built-with-love.svg)](https://github.com/lucasliano/td2project)
[![forthebadge](https://forthebadge.com/images/badges/made-with-c.svg)](https://github.com/lucasliano/td2project)
[![forthebadge](https://forthebadge.com/images/badges/not-a-bug-a-feature.svg)](https://github.com/lucasliano/td2project)
[![forthebadge](https://forthebadge.com/images/badges/powered-by-coffee.svg)](https://github.com/lucasliano/td2project)



> :warning: **Work In Progress** :warning:


<!-- PROJECT LOGO -->
<br />
<p align="center">
  <a href="https://github.com/lucasliano/td2project">
    <img src="diagrama/logo.png" alt="Logo" width="200" height="200">
  </a>

  <h3 align="center">Security Alarm System</h3>
  
  <p align="center">
    This security system project is the final assignment of the digital technics II subjects at Universidad Tecnológica Nacional.
    <br />
    <a href="https://github.com/lucasliano/td2project"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/lucasliano/td2project">View Demo</a>
    ·
    <a href="https://github.com/lucasliano/td2project/issues">Report Bug</a>
    ·
    <a href="https://github.com/lucasliano/td2project/issues">Request Feature</a>
  </p>
</p>

<!-- TABLE OF CONTENTS -->
<details open="open">
  <summary><h2 style="display: inline-block">Table of Contents</h2></summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ol>
      <li><a href="#system-diagram">System Diagram</a></li>
      <li><a href="#main-board-pcb-and-schematics">Main Board PCB and Schematics</a></li>
      <li><a href="#equipment">Equipment</a></li>
    </ol>
    </li>
    <li><a href="#authors">Authors</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
  </ol>
</details>


## About The Project

The main idea of this project is to build a systems which allows you to detect motion in different zones within your home.  

The activation/deactivation of the system is meant to be controlled using an android app or directly trough the front keyboard. At the same time, it would be possible to configure the system to deactivate the alarm in presence of a known RFID card.

Should an error occurred, a notification will be sent to the mobile device and it will be logged into the internal EEPROM memory. The system also takes into account possible disconnections from the power supply. 

#### System Diagram
<p align="center">
  <a href="https://github.com/lucasliano/td2project">
    <img src="diagrama/Diagrama.png" alt="diagrama">
  </a>
</p>

### Main Board PCB and Schematics

#### Schematics
The main board does not present many difficulties. The biggest circuit used is a battery charger and power supply source administrator. You will find this schematic in a PDF file in the ``` PCB_files_kicad ``` folder.

<p align="center">
  <a href="https://github.com/lucasliano/td2project/blob/main/PCB_files_kicad/Schematic%20v1.2.pdf">
    <img src="PCB/schematic_preview.png" alt="diagrama">
  </a>
</p>

### Equipment

<table>
  <thead>
    <tr>
      <th>Component</th>
      <th>Qty</th>
      <th>Unit Price (ARS)</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>
        <p>STM32 Blue Pill</p>
        <img src="diagrama/Bluepill.png" width="200" height="100">
      </td>
      <td>1</td>
      <td>$1200</td>
    </tr>
    <tr>
      <td>
        <p>Bluetooth</p>
        <img src="diagrama/BT.png" width="200" height="200">
      </td>
      <td>1</td>
      <td>$700</td>
    </tr>
    <tr>
      <td>
        <p>RFID Sensor</p>
        <img src="diagrama/RFID.png" width="200" height="200">
      </td>
      <td>1</td>
      <td>$500</td>
    </tr>
    <tr>
      <td>
        <p>I2C - LCD Display</p>
        <img src="diagrama/LCD.png" width="200" height="200">
      </td>
      <td>1</td>
      <td>$900</td>
    </tr>
    <tr>
      <td>
        <p>IR Sensor</p>
        <img src="diagrama/Sensor.png"  width="200" height="200">
      </td>
      <td>2</td>
      <td>$250</td>
    </tr>
    <tr>
      <td>
        <p>Keyboard</p>
        <img src="diagrama/Teclado.png"  width="200" height="200">
      </td>
      <td>1</td>
      <td>$160</td>
    </tr>
    <tr>
      <td>
        <p>EEPROM Memory</p>
        <img src="diagrama/eeprom.png"  width="200" height="200">
      </td>
      <td>1</td>
      <td>$300</td>
    </tr>
    <tr>
      <td>
        <p>DC-DC Booster</p>
        <img src="diagrama/MT3608.png"  width="200" height="150">
      </td>
      <td>1</td>
      <td>$250</td>
    </tr>
    <tr>
      <td>
        <p>Buzzer</p>
        <img src="diagrama/buzzer.png"  width="200" height="200">
      </td>
      <td>1</td>
      <td>$160</td>
    </tr>
    <tr>
      <td>
        <p>Li-Ion battery</p>
        <img src="diagrama/Batteries.png"  width="200" height="200">
      </td>
      <td>1</td>
      <td>$500</td>
    </tr>
  </tbody>
</table>


<!-- Authors -->
## Authors
* Liaño, Lucas
* Golob, Lautaro Francisco
* Crisafio, Gabriel
* Dieguez, Manuel


<!-- LICENSE -->
## License

Distributed under the GPL-3.0 License. See `LICENSE` for more information.

<!-- CONTACT -->
## Contact

Lucas Liaño - lliano@frba.utn.edu.ar

Repo Link: [https://github.com/lucasliano/td2project](https://github.com/lucasliano/td2project)
