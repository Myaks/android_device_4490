## Specify phone tech before including full_phone
$(call inherit-product, vendor/cm/config/gsm.mk)

# Release name
PRODUCT_RELEASE_NAME := nano4

# Inherit some common CM stuff.
$(call inherit-product, vendor/cm/config/common_full_phone.mk)

# Inherit device configuration
$(call inherit-product, device/fly/nano4/full_nano4.mk)

PRODUCT_BUILD_PROP_OVERRIDES += \
    PRODUCT_NAME=nano \
    TARGET_DEVICE=nano \
    BUILD_FINGERPRINT="fly/mintxx/nano:4.1.2/JZO54K/S5282XXANF3:user/release-keys" \
    PRIVATE_BUILD_DESC="mintxx-user 4.1.2 JZO54K S5282XXANF3 release-keys"
    

PRODUCT_NAME := cm_nano4
PRODUCT_DEVICE := nano4
