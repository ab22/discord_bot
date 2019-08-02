# Discord Bot

A pet project discord bot

## Building

When building, a `QTPATH` variable must be specified in order to build the UI. If the variable is not defined, then a default path is taken based on my local config.

```
mkdir build && cd build/
cmake ..
```

To specify a QTPATH variable you can use:

```
> QTENV="/path/to/qt" cmake ..
   or
> cmake -DQTENV="/path/to/qt" cmake ..
```
