<h1 align="center">
    PSO2 Tweaker - Damage Dump Plugin
</h1>

<p align="center">
    <a href="https://github.com/approved/PSO2DamageDump/blob/master/LICENSE">
        <img alt="repository license" src="https://img.shields.io/github/license/approved/PSO2DamageDump?style=for-the-badge"/>
    </a>
    <a href="https://github.com/approved/PSO2DamageDump/releases">
        <img alt="release version" src="https://img.shields.io/github/v/tag/approved/PSO2DamageDump?style=for-the-badge&logo=C%2B%2B"/>
    </a>
    <a href="https://github.com/approved/PSO2DamageDump/graphs/contributors">
        <img alt="GitHub contributors" src="https://img.shields.io/github/contributors/approved/PSO2DamageDump?color=green&logo=github&style=for-the-badge"/>
    </a>
</p>


## Table of Contents
- [About](#about)
- [Motivations](#motivations)
- [Usage](#usage)
  - [Prerequisites](#prerequisites)
  - [Obtaining Plugin](#obtaining-plugin)
  - [Installation](#installation)
- [Disclaimer](#disclaimer)
- [Acknowledgements](#acknowledgments)


## About
This repository features a game plugin that logs player damage for the Japanese version of the game [Phantasy Star Online 2 (PSO2)](https://pso2.jp/), using the tool [PSO2 Tweaker](https://arks-layer.com/). The plugin enables users to track detailed metrics for all players in a mission (e.g. damage output per second, critical hits, proportion of total damage dealt, etc).

Internally, the plugin intercepts game client packets containing player damage data and logs the damage numbers to a CSV file, which is usable by other upstream applications (e.g. a game overlay such as [OverParse](https://github.com/mysterious64/OverParse)).


## Motivations
In PSO2, player damage data is not usefully presented to its players; damage data is only available through brief screen pop-ups when a player deals damage. Players desiring to optimize their gameplay are unable to effectively maximize their damage output per second without the assistance of an external tool, such as this plugin.

This project is a derivative work of the [original open-sourced PSO2 plugin](https://github.com/VariantXYZ/PSO2DamageDump) authored by [VariantXYZ](https://github.com/VariantXYZ); however, it is no longer maintained and is currently incompatible with PSO2 and PSO2 Tweaker. PSO2 Tweaker independently maintains a working fork of the plugin using the same CSV file format, but it is unfortunately closed-source. Without an open-source alternative, it is difficult for developers to further extend new functionalities; thus, this project was created to maintain an extensible working open-source fork.


## Usage
The following sections detail how to install this plugin for PSO2. While the produced data file is relatively human-readable, it is highly recommended to use this plugin in conjunction with an upstream application to more effectively interpret the damage data, such as with the game overlay [OverParse](https://github.com/mysterious64/OverParse).

### Prerequisites
This plugin requires an installation of the Japanese version of [Phantasy Star Online 2](https://pso2.jp/) with the [PSO2 Tweaker](https://arks-layer.com/) tool installed. The setup guides for these prerequisite software are available here:
- [Phantasy Star Online 2: Setup](http://pso2.jp/players/manual/setup/pc/)
- [PSO2 Tweaker: Setup](https://arks-layer.com/setup.html)

### Obtaining Plugin
There are 2 methods for obtaining this project's compiled plugin file, `PSO2DamageDump.dll`:
- (recommended) downloading directly from [GitHub releases](https://github.com/approved/PSO2DamageDump/releases)
- building from the cloned project sources with `msbuild` (available with Visual Studio 2019+ and the `Desktop development with C++` toolchain; select `Build | Build Solution`).


### Installation
The obtained plugin file `PSO2DamageDump.dll` must be installed in the `plugins` folder within the game's root installation directory. For example, the game's installation directory would look similar to the following:

```
+ data
+ licenses
+ sys
+ ...
+ plugins
 - PSO2DamageDump.dll
- ...
- pso2launcher.exe
- ...
```


## Disclaimer
The use of any software that modifies the game client (e.g. PSO2 Tweaker, this plugin, etc) is a direct violation of PSO2's Terms of Service and is grounds for account suspension. The use of this plugin and any associated software is at your own risk.

An official announcement from PSO2 relating to this topic is available [here](http://pso2.jp/players/news/9224/).
<details>
    <summary>English translation</summary>
    ```
    The "PSO2" management team has confirmed the existence of an external tool that analyzes and acquires the internal information and numerical values of "PSO2".
    
    Using such an external tool is a violation of the Terms of Service, which violates Article 9 of the Terms of Service (Prohibition of cheating and cheating).
    
    We take measures to block access from external tools at any time, but if it is confirmed that such a tool is being used in the future, we will suspend the use of the corresponding account without notice based on the terms of use. Therefore, please do not use it.
    ```
</details>


## Acknowledgments
This project is a derivative work of [@VariantXYZ]'s public work, however it has been significantly rewritten to fix compatibility issues with the latest versions of PSO2 and PSO2 Tweaker.
