# wrtele

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

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
* `WRTELE_MAC_ADDRS`: semicolon `;` separated list of MAC addresses to watch.
* `WRTELE_LIST_COMMAND`: semicolon `;`, comma `,` or space separated list of
  commands to run to get MAC addresses. (E.g. `iwinfo wlan0 assoclist`)
* `WRTELE_SLEEP_DURATION`: duration in seconds to sleep between each check.
