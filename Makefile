# SPDX-License-Identifier: MIT
# Copyright (c) 2021 Chua Hou

include $(TOPDIR)/rules.mk

PKG_NAME    := wrtele
PKG_RELEASE := 0.1.0.0

PKG_BUILD_DIR := $(BUILD_DIR)/$(PKG_NAME)

include $(INCLUDE_DIR)/package.mk

define Package/wrtele
	SECTION  := utils
	CATEGORY := Utilities
	TITLE    := wrtele
	DEPENDS  := +libcurl
endef

define Package/wrtele/description
	Telegram bot that informs when certain devices connect and disconnect.
endef

define Build/Prepare
	make -C src clean
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) -r ./src/. $(PKG_BUILD_DIR)/
endef

define Package/wrtele/install
	$(INSTALL_DIR) $(1)/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/bin/wrtele $(1)/bin/
endef

$(eval $(call BuildPackage,wrtele))
