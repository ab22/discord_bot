# Discord Bot

A pet project discord bot

## Building

When building, a `QTPATH32` or `QTPATH64` variable must be specified in order to build the UI.

To build the project, create a `build/` folder for 32bit or `build64/` folder for 64bit. Those two folder names are already added to the `.gitignore` file so no need to worry
about committing them:

```
mkdir build && cd build/
cmake ..
```

To specify a QTPATH variable you can use:

```
QTPATH64="/path/to/qt" cmake ..
```
or
```
cmake -DQTPATH64="/path/to/qt" cmake ..
```
