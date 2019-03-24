#!/usr/bin/env python
"""pi4home setup script."""
from setuptools import setup, find_packages
import os

from pi4home import const

PROJECT_NAME = 'pi4home'
PROJECT_PACKAGE_NAME = 'pi4home'
PROJECT_LICENSE = 'MIT'
PROJECT_AUTHOR = 'PI4Home'
PROJECT_COPYRIGHT = '2019, PI4Home'
PROJECT_URL = 'https://github.com/khzd/pi4home/'
PROJECT_EMAIL = 'contact@github.com/khzd/pi4home'

PROJECT_GITHUB_USERNAME = 'pi4home'
PROJECT_GITHUB_REPOSITORY = 'pi4home'

PYPI_URL = 'https://pypi.python.org/pypi/{}'.format(PROJECT_PACKAGE_NAME)
GITHUB_PATH = '{}/{}'.format(PROJECT_GITHUB_USERNAME, PROJECT_GITHUB_REPOSITORY)
GITHUB_URL = 'https://github.com/{}'.format(GITHUB_PATH)

DOWNLOAD_URL = '{}/archive/v{}.zip'.format(GITHUB_URL, const.__version__)

REQUIRES = [
    'voluptuous>=0.11.5,<0.12',
    'PyYAML>=5.1,<6',
    'paho-mqtt>=1.4,<2',
    'colorlog>=4.0.2',
    'tornado>=5.1.1,<6',
    'typing>=3.6.6;python_version<"3.5"',
    'protobuf>=3.7,<3.8',
    'tzlocal>=1.5.1',
    'pyserial>=3.4,<4',
    'ifaddr>=0.1.6,<1',
]

# If you have problems importing platformio and esptool as modules you can set
# $PI4HOME_USE_SUBPROCESS to make PI4Home call their executables instead.
# This means they have to be in your $PATH.
if os.environ.get('PI4HOME_USE_SUBPROCESS') is None:
    REQUIRES.extend([
        'platformio>=3.6.5',
        'esptool>=2.6,<3',
    ])

CLASSIFIERS = [
    'Environment :: Console',
    'Intended Audience :: Developers',
    'Intended Audience :: End Users/Desktop',
    'License :: OSI Approved :: MIT License',
    'Programming Language :: C++',
    'Programming Language :: Python :: 2',
    'Programming Language :: Python :: 3',
    'Topic :: Home Automation',
]

setup(
    name=PROJECT_PACKAGE_NAME,
    version=const.__version__,
    license=PROJECT_LICENSE,
    url=GITHUB_URL,
    download_url=DOWNLOAD_URL,
    author=PROJECT_AUTHOR,
    author_email=PROJECT_EMAIL,
    description="Make creating custom firmwares for Pi platforms super easy.",
    include_package_data=True,
    zip_safe=False,
    platforms='any',
    test_suite='tests',
    python_requires='>=2.7,!=3.0.*,!=3.1.*,!=3.2.*,!=3.3.*,!=3.4.*,<4.0',
    install_requires=REQUIRES,
    keywords=['home', 'automation'],
    entry_points={
        'console_scripts': [
            'pi4home = pi4home.__main__:main',
            'pi4homeyaml = pi4home.legacy:main'
        ]
    },
    packages=find_packages()
)
