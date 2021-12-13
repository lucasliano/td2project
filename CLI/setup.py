from setuptools import setup, find_packages


setup(
    name='td2project',
    author='lucas',
    author_email='lliano@frba.utn.edu.ar',
    packages = find_packages('.'),
    install_requires=[
        'pybluez',
    ],
    entry_points = {
        'console_scripts': [
            'read_mem = td2project.client:read_mem',
            'set_pass = td2project.client:set_pass',
        ]
    }
)
