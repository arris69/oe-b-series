DESCRIPTION = "GNOME XML Parser library"
SECTION = "libs"
PRIORITY = "optional"
LICENSE = "MIT"
DEPENDS_virtclass-native = "python-native"

SRC_URI = "ftp://xmlsoft.org/libxml2/libxml2-${PV}.tar.gz;name=archive"
S = "${WORKDIR}/${BPN}-${PV}"

INC_PR = "r8"

BBCLASSEXTEND = "native"

inherit autotools pkgconfig binconfig

EXTRA_OECONF = "\
 --without-debug \
 --without-legacy \
 --with-catalog \
 --with-docbook \
 --with-c14n"

XPY = " --without-python"
XPY_virtclass-native = " --with-python=${PYTHON_DIR}" 

EXTRA_OECONF += "${XPY}"

export LDFLAGS += "-ldl"

do_install_append() {
	install -d ${D}${datadir}/aclocal
 	install -m 0644 libxml.m4 ${D}${datadir}/aclocal
	#this is need it by php during its install
	install -d ${STAGING_BINDIR_CROSS}
	install -m 0755 xml2-config ${STAGING_BINDIR_CROSS}/
}

do_install_append_virtclass-native() {
	:
}

DEBIANNAME_${PN} = "libxml2"

PACKAGES =+ "${PN}-utils"
FILES_${PN} = "${libexecdir}/* ${libdir}/lib*${SOLIBS} \
            ${sysconfdir} ${sharedstatedir} ${localstatedir} \
            ${base_libdir}/*${SOLIBS} \
            ${datadir}/${PN} ${libdir}/${PN}/* \
            ${datadir}/pixmaps ${datadir}/applications \
            ${datadir}/idl ${datadir}/omf ${datadir}/sounds \
            ${libdir}/bonobo/servers"

FILES_${PN}-dev += "${bindir}/*-config"
FILES_${PN}-utils = "${bindir}/xmllint ${bindir}/xmlcatalog ${libdir}/*.sh"
