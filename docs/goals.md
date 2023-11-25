# Goal's of this Project

Early on in my career I wrote Arduino sketches for some hobby applications. They were small, simple, and did the job. But debugging and testing was tedious - you had to upload the sketch to your controller ever time you wanted to make a change and test it manually.

Having now spent over a decade working in software engineering, I realize we can do more. My goal with this project is to apply several principles of modern software development to an Arduino sketch, and to gain the practice of doing them with C++. My hope is that my examples of applying these practices an ideas encourages others to grow further in their coding journey and apply some of these concepts themselves.

## Modern Software Architectures and Design Principles

In my day job we often apply architecture ideas like Clean Architecture (I'm a fan of this [].NET implementation](https://github.com/ardalis/CleanArchitecture)) and [SOLID](https://en.wikipedia.org/wiki/SOLID). These patterns trade adding some complexity in the design and layout of the code for flexibility and extensibilty. Object-oriented objects and single-purpose functions are easier to test and become confident in their behavior. Defining and inheriting interfaces makes it easy to swap one component for another. Although there isn't a lot of reusability within this sketch, hopefully building objects in this way demonstrates an example of what's possible on the Arduino platform, and gives others options and tools to copy and reuse.

## Automated Testing

Manual testing is common for entry-level embedded systems like Arduino, but in the professional space automated testing is a much. Writing tests as code enables making sure tests run the same way, every time. They can also run much faster. Having good tests in places brings trust and safety; you know that if you make a change to one part of the software that you will be alerted if that negatively impacts something else. This project uses [AUnit](https://github.com/bxparks/AUnit) for its test framework.

## Continuous Integration

Going one step further from automated testing is being able to quickly integrate changes. Typically for an Arduino-based system, running tests (manually or automated) requires uploading the sketch to a real microcontroller (in AirGradient's case an ESP8266) and running the tests. [EpoxyDuino](https://github.com/bxparks/EpoxyDuino) is an implementation of Arduino on Linux. Being able to run Arduino code without physical Arduino hardware speeds up the development process tremendously. You can come up with a new idea, write the code and tests in minutes, and run the tests in seconds. No need to have a physical device on-hand, plug it into a computer, select the appropriate port, or to wait for the upload to complete. No need to repeat these manual steps every time you make a change.

Manually testing on physical hardware is still important, but combining automated tests and continuous integration means the majority of the effort can be done without the hardware.
