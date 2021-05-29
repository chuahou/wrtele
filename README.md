# wrtele

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

Telegram bot that runs on OpenWRT that informs when certain devices connect and
disconnect.

## Build process

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
