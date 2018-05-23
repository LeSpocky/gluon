include $(TOPDIR)/rules.mk

PKG_NAME:=uc
PKG_VERSION:=1

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL=https://github.com/christf/uc.git
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE_VERSION:=2392a3cb8daa60a63b90aadd1771995eaf323b23
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION)-$(PKG_SOURCE_VERSION).tar.gz


include $(INCLUDE_DIR)/package.mk


define Package/uc
  SECTION:=Utilities
  CATEGORY:=Tools
  TITLE:=small utility to write to a unix socket and obtain response
endef

define Package/uc/description
 uc can be used to pipe a command into a unix socket and to read and display the corresponding response.
endef

MAKE_FLAGS+= \
        CFLAGS="$(TARGET_CFLAGS)" \
        LDLIBS="" \

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
endef

define Package/uc/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/uc $(1)/usr/bin
endef

$(eval $(call BuildPackage,uc))
