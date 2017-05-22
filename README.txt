Welche GLIBC ist verfügbar
    strings /usr/lib/arm-linux-gnueabihf/libstdc++.so.6 | grep -i glibc

Aktuell!

Anzeige Libray-Typ
    readelf -A libmyLib.so

    Attribute Section: aeabi
    File Attributes
      Tag_CPU_name: "ARM1176JZF-S"
      Tag_CPU_arch: v6KZ
      Tag_ARM_ISA_use: Yes
      Tag_THUMB_ISA_use: Thumb-1
      Tag_FP_arch: VFPv2
      Tag_ABI_PCS_wchar_t: 4
      Tag_ABI_FP_rounding: Needed
      Tag_ABI_FP_denormal: Needed
      Tag_ABI_FP_exceptions: Needed
      Tag_ABI_FP_number_model: IEEE 754
      Tag_ABI_align_needed: 8-byte
      Tag_ABI_align_preserved: 8-byte, except leaf SP
      Tag_ABI_enum_size: int
      Tag_ABI_VFP_args: VFP registers
      Tag_CPU_unaligned_access: v6
      Tag_Virtualization_use: TrustZone

Lib bei ldconfig bekannt machen
    sudo mv libmyLib.so /usr/lib
    sudo ldconfig

    ldconfig -p | grep -i libmylib
        libmyLib.so (libc6,hard-float) => /usr/lib/libmyLib.so

C++ - Samples
        http://www.cppsamples.com/

Dependencies für dieses Projekt:
    git submodule update --init -- .dependencies/args
    git submodule update --init -- .dependencies/fmt
    git submodule update --init -- .dependencies/googletest/
    git submodule update --init -- .dependencies/spdlog
    git submodule update --init -- .dependencies/uws

    Google Test
        git submodule add https://github.com/google/googletest .dependencies/googletest
        git submodule add https://github.com/uWebSockets/uWebSockets .dependencies/uws
        git submodule add https://github.com/nlohmann/json .dependencies/json

ACHTUNG:
    clang auf Raspi needs crtbegin.o - wird nicht automatisch installiert
        apt-get install --reinstall libgcc-4.9-dev
