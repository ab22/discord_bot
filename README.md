# Discord Bot

A pet project discord bot

## Building

In order to build the UI, the environment variables `QT5_PATH` or `QT5_PATH64` must be set. This depends on whether a 64bit or 32bit application was detected.

To build the project, create a `build/` folder for 32bit or `build64/` folder for 64bit. Those two folder names are already added to the `.gitignore` file so no need to worry
about committing them:

```
mkdir build && cd build/
cmake ..
```

To specify a QT5_PATH variable you can use:

```
QT5_PATH64="/path/to/qt" cmake ..
```
or
```
cmake -DQT5_PATH64="/path/to/qt" cmake ..
```
