# Run-Time Type Information

For this sketch I tried to implement and apply Object Oriented Programming techniques were it made sense. I had thought I might reuse the State Machine concept, and built `MachineBase` and `StateBase` to be extendable.

The different `ConfigStateMachine` states like `ClearState` implement `StateBase` and its references to `MachineBase`, but require awareness of the `ConfigStateMachine` in order to write to the OLED display. To do this, `ClearState` requires Run-Time Type Information (RTTI) so that it can `dynamic_cast<>` a `MachineBase` to `ConfigStateMachine`.

Many embedded systems do not support RTTI, and for this reason the Arduino compiler disables it by default. An ESP8266 **can** support RTTI, but to provide Arduino support, the ESP Arduino core implementation avoids its use and implements `TypeConversionFunctions` combined with Enums. Applied to our case, `MachineBase` gets a `MachineType` Enum. Other objects and classes can read the Enum and determine what type the `MachineBase` implementation it is.

I prefer use of `dynamic_cast<>` because I feel it helps satisfy SOLID. TODO - finish this statement.

This sketch includes both an implementation that avoids use of RTTI and one that leverages it. TODO - get the `#if` directives working properly to easily switch.

A file called `platform.txt` contains the compiler flags for a particular board. On Windows I found mine at this path: `C:\Users\USERNAME\AppData\Local\Arduino15\packages\esp8266\hardware\esp8266\3.1.2\platform.txt`.

I replaced the original line:

```
compiler.cpp.flags=-c "{compiler.warning_flags}-cppflags" {build.stacksmash_flags} -Os -g -free -fipa-pta -Werror=return-type -mlongcalls -mtext-section-literals -fno-rtti -falign-functions=4 {build.stdcpp_level} -MMD -ffunction-sections -fdata-sections {build.exception_flags} {build.sslflags} {build.mmuflags} {build.non32xferflags}
```

With this alternative that swapps the `fno-rtti` flag for `-frtti`:

```
compiler.cpp.flags=-c "{compiler.warning_flags}-cppflags" {build.stacksmash_flags} -Os -g -free -fipa-pta -Werror=return-type -mlongcalls -mtext-section-literals -frtti -falign-functions=4 {build.stdcpp_level} -MMD -ffunction-sections -fdata-sections {build.exception_flags} {build.sslflags} {build.mmuflags} {build.non32xferflags}
```

This enables RTTI with the ESP8266 and facilitates using `dynamic_cast<>`.