# Contributing to PI4Home

This python project is responsible for reading in YAML configuration files,
converting them to C++ code. This code is then converted to a platformio project and compiled
with [pi4home-core](https://github.com/khzd/pi4home/pi4home-core), the C++ framework behind the project.

For a detailed guide, please see https://github.com/khzd/pi4home/guides/contributing.html#contributing-to-pi4homeyaml

Things to note when contributing:

 - Please test your changes :)
 - If a new feature is added or an existing user-facing feature is changed, you should also 
   update the [docs](https://github.com/khzd/pi4home/pi4home-docs). See [contributing to pi4home-docs](https://github.com/khzd/pi4home/guides/contributing.html#contributing-to-pi4homedocs)
   for more information.
 - Please also update the tests in the `tests/` folder. You can do so by just adding a line in one of the YAML files
   which checks if your new feature compiles correctly.
 - Sometimes I will let pull requests linger because I'm not 100% sure about them. Please feel free to ping
   me after some time.
