DESCRIPTION = "The GNU cc and gcc C compilers."
HOMEPAGE = "http://www.gnu.org/software/gcc/"
SECTION = "devel"
LICENSE = "GPL"

NATIVEDEPS = ""

inherit autotools gettext

FILESDIR = "${@os.path.dirname(bb.data.getVar('FILE',d,1))}/gcc-${PV}"

COMPATIBLE_TARGET_SYS ?= "(?!nios2)"

# When making a Canadian SDK, we use these files too to make the compiler
# for building for the new host part.  So only obey TARGET_FPU for the
# real target.
def get_gcc_fpu_setting(bb, d):
    if bb.data.getVar('TARGET_FPU', d, 1) in [ 'soft' ] and bb.data.getVar('TARGET_OS', d, 1).find('linux') >= 0 :
        return "--with-float=soft"
    return ""

def get_gcc_mips_plt_setting(bb, d):
    if bb.data.getVar('TARGET_ARCH', d, 1) in [ 'mips', 'mipsel' ] and 'mplt' in bb.data.getVar('DISTRO_FEATURES',d,1).split() :
        return "--with-mips-plt"
    return ""

# We really need HOST_SYS here for some packages and TARGET_SYS for others.
# For now, libgcc is most important so we fix for that - RP.
SHLIBSDIR = "${STAGING_DIR_TARGET}/shlibs"

DEBIANNAME_libgcc = "libgcc1"

MIRRORS_prepend () {
${GNU_MIRROR}/gcc/releases/    ftp://gcc.gnu.org/pub/gcc/releases/
${GNU_MIRROR}/gcc/	http://mirrors.rcn.net/pub/sourceware/gcc/releases/
${GNU_MIRROR}/gcc/releases/    http://gcc.get-software.com/releases/
${GNU_MIRROR}/gcc/	http://gcc.get-software.com/releases/
}

#
# Set some default values
#
gcclibdir = "${libdir}/gcc"
BINV = "${PV}"
S = "${WORKDIR}/gcc-${PV}"
B = "${S}/build.${HOST_SYS}.${TARGET_SYS}"

