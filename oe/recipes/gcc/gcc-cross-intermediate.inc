DEPENDS = "virtual/${TARGET_PREFIX}binutils ${NATIVEDEPS}"
DEPENDS += "virtual/${TARGET_PREFIX}libc-initial"
PROVIDES = "virtual/${TARGET_PREFIX}gcc-intermediate"
PACKAGES = ""

# This is intended to be a -very- basic config
# sysroot is needed in case we use libc-initial
EXTRA_OECONF = "--with-local-prefix=${STAGING_DIR_TARGET}${target_prefix} \
		--enable-shared \
		--disable-multilib \
		--disable-threads \
		--enable-languages=c \
		--program-prefix=${TARGET_PREFIX} \
		${EXTRA_OECONF_PATHS} \
		${OPTSPACE} \
		${EXTRA_OECONF_INTERMEDIATE} \
		${@get_gcc_fpu_setting(bb, d)} \
		${@get_gcc_mips_plt_setting(bb, d)}"

do_install () {
	oe_runmake 'DESTDIR=${D}' install

    # If this is important, we should remove the staging package here
	# get rid of dummy libc.so
	#if [ -z "`file ${STAGING_DIR_TARGET}${target_libdir}/libc.so | grep "ASCII C program text"`" ]; then
	#	rm -rf ${STAGING_DIR_TARGET}${target_libdir}/libc.so
	#fi
}
