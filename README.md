# wrtele

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/chuahou/wrtele.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/chuahou/wrtele/context:cpp)
[![Total alerts](https://img.shields.io/lgtm/alerts/g/chuahou/wrtele.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/chuahou/wrtele/alerts/)

Telegram bot that runs on OpenWRT that informs when certain devices connect and
disconnect.

## Build process

Firstly, perform configuration by making a copy of `config.tmpl.h` into
`config.h` in the `src` directory, filling in the options.

If using Nix, first enter the `devShell` to make build tools available.

	nix develop

Enter the root directory of your copy of the OpenWRT SDK, then clone this
repository into `package/wrtele`. If necessary, configure the build and install
`libcurl`.

	make menuconfig
	./scripts/feeds update -a
	./scripts/feeds install libcurl
	make package/wrtele/compile

Then copy `bin/packages/<arch>/base/wrtele_<release>_<arch>.ipk` to the router and
install it with `opkg install`.

Since the build process is impure using `feeds`, a pure Nix build is KIV.

## Usage

Simply run the binary with no arguments, and give configuration using
environment variables.

* `WRTELE_TELE_API_KEY`: Telegram Bot API key.
* `WRTELE_TELE_TARGET_CHAT_ID`: Chat ID to send updates to.
* `WRTELE_MAC_ADDRS`: semicolon `;` or comma `,` separated list of MAC addresses
  to watch. To name a device with MAC `<mac>` with name `<name>`, write
  `<mac>=<name>`.
* `WRTELE_LIST_COMMAND`: semicolon `;` separated list of
  commands to run to get MAC addresses. (E.g. `iwinfo wlan0 assoclist`)
* `WRTELE_SLEEP_DURATION`: duration in seconds to sleep between each check.

To run as an [init script](https://openwrt.org/docs/techref/initscripts), write
something like this in `/etc/init.d/wrtele`:

```sh
#!/bin/sh /etc/rc.common

START=99
STOP=00

start () {
	export WRTELE_TELE_API_KEY="[Telegram bot API key]"
	export WRTELE_TELE_TARGET_CHAT_ID="[Telegram chat ID]"
	export WRTELE_MAC_ADDRS="AA:BB:CC:DD:EE:FF=Device name;BB:CC:DD:EE:FF:00=Another Device"
	export WRTELE_LIST_COMMAND="iwinfo wlan0 assoclist;iwinfo wlan1 assoclist"
	export WRTELE_SLEEP_DURATION=10

	LOG_FILE=/var/log/wrtele
	[ -f $LOG_FILE ] && rm $LOG_FILE
	wrtele > $LOG_FILE 2>&1 &
}

stop () {
	killall wrtele
}
```
