# FlexCat (Flexible Translation Catalogs for Amiga systems)

[![Build Status](https://travis-ci.org/adtools/flexcat.svg?branch=master)](https://travis-ci.org/adtools/flexcat)
[![Code Climate](https://codeclimate.com/github/adtools/flexcat/badges/gpa.svg)](https://codeclimate.com/github/adtools/flexcat)
[![License](http://img.shields.io/:license-gpl2-blue.svg?style=flat)](http://www.gnu.org/licenses/gpl-2.0.html)
[![Github Issues](http://githubbadges.herokuapp.com/adtools/flexcat/issues.svg)](https://github.com/adtools/flexcat/issues)

FlexCat is a tool to create Amiga localization catalogs (*.catalog files) similar to what the good-old CatComp tool does. However, it can also create source and header files for developers and can be used on other platforms (Unix, Windows, etc.), thus is cross-platform aware. The difference between FlexCat and KitCat, CatComp and some others is, that FlexCat is designed to produce any source you want:  any programming language, any individual needs should be satisfied. However, FlexCat is not more difficult to use. This sounds like a contradiction. FlexCat's solution is to use template files, the so called "source descriptions". Ready to use examples for Assembler, C, C++, E, Oberon and Modula-2 are distributed, additionally an example for supporting catalogs on Workbench 2.0. Any other examples are welcome.

## Features

* Runs on any computer (I hope)
* Fully portable (versions for AmigaOS3, AmigaOS4, MorphOS, AROS, Linux (i386) and Windows)
* Localized of course ;-) (AmigaOS versions only)
* Can produce catalog handling source code for any language (templates for Assembler, C, C++, E, Oberon and Modula-2 included)
* Written by the people who use it daily (so it should cover all your needs)

## Requirements

FlexCat works on any Amiga, however you need AmigaOS 2.04 or higher to make it using the localization for own purposes. Also processor better or equal to 68020. In addition, a Linux version (i386) and Windows version is included so that the FlexCat functionality can even be used in cross-compiler environments.

## Downloads/Releases

All releases up to the most current ones can be downloaded from our [central releases management](https://github.com/adtools/flexcat/releases).

## Development / Contributing

If you got any programming skill (no beginners pliz!) and some spare time you can add whatever you want. Contributing your own code/modifications to FlexCat is quite straight forward since you can use the nice resources of GitHub and submit your changes in terms of [pull requests](https://github.com/adtools/flexcat/pulls). If you, however, feel you might be better suited by join ing our development team directly and you would like to directly submit your changes to this code repository we could easily provide you direct write access.

## License & Copyright

FlexCat is distributed and license under the GNU General Public License Version 2. See [COPYING](COPYING) for more detailed information.

## Authors

* Jens Maus
* Jochen Wiedmann
* Marcin Orlowski
* Pavel Fedin
* Thore Böckelmann
