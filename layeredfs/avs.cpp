#include <windows.h>
#include <stdio.h>

#include "avs.h"
#include "hook.h"
#include "3rd_party/MinHook.h"
#include "utils.h"

#define AVS_STRUCT_DEF(ret_type, name, ...) char* name;

typedef struct {
    char *version_name;
    char *unique_check; // for IIDX vs SDVX cloud, almost all funcs are identical

    FOREACH_AVS_FUNC(AVS_STRUCT_DEF)
} avs_exports_t;

const LPCWSTR dll_names[] = {
    L"libavs-win32.dll",
    L"libavs-win64.dll",
    L"avs2-core.dll",
};

const avs_exports_t avs_exports[] = {
    [&] { avs_exports_t x = { 0 };
    x.version_name                        = "normal";
    x.unique_check                        = NULL;
    x.avs_fs_open                         = "avs_fs_open";
    x.avs_fs_close                        = "avs_fs_close";
    x.avs_fs_convert_path                 = "avs_fs_convert_path";
    x.avs_fs_read                         = "avs_fs_read";
    x.avs_fs_lseek                        = "avs_fs_lseek";
    x.avs_fs_fstat                        = "avs_fs_fstat";
    x.avs_fs_lstat                        = "avs_fs_lstat";
    x.avs_fs_mount                        = "avs_fs_mount";
    x.mdigest_create                      = "mdigest_create";
    x.mdigest_update                      = "mdigest_update";
    x.mdigest_finish                      = "mdigest_finish";
    x.mdigest_destroy                     = "mdigest_destroy";
    x.property_read_query_memsize         = "property_read_query_memsize";
    x.property_read_query_memsize_long    = "property_read_query_memsize_long";
    x.property_create                     = "property_create";
    x.property_desc_to_buffer             = "property_desc_to_buffer";
    x.property_insert_read                = "property_insert_read";
    x.property_mem_write                  = "property_mem_write";
    x.property_destroy                    = "property_destroy";
    x.property_node_query_stat            = "property_node_query_stat";
    x.cstream_create                      = "cstream_create";
    x.cstream_operate                     = "cstream_operate";
    x.cstream_finish                      = "cstream_finish";
    x.cstream_destroy                     = "cstream_destroy";
    return x;
    }(),
    [&] { avs_exports_t x = { 0 };
    x.version_name                        = "SDVX";
    x.unique_check                        = NULL;
    x.avs_fs_open                         = "XCd229cc000090";
    x.avs_fs_close                        = "XCd229cc00011f";
    x.avs_fs_convert_path                 = "XCd229cc00001e";
    x.avs_fs_read                         = "XCd229cc00010d";
    x.avs_fs_lseek                        = "XCd229cc00004d";
    x.avs_fs_fstat                        = "XCd229cc0000c3";
    x.avs_fs_lstat                        = "XCd229cc0000c0";
    x.avs_fs_mount                        = "XCd229cc0000ce";
    x.mdigest_create                      = "XCd229cc00003d";
    x.mdigest_update                      = "XCd229cc000157";
    x.mdigest_finish                      = "XCd229cc000015";
    x.mdigest_destroy                     = "XCd229cc000050";
    x.property_read_query_memsize         = "XCd229cc0000ff";
    x.property_read_query_memsize_long    = "XCd229cc00002b";
    x.property_create                     = "XCd229cc000126";
    x.property_desc_to_buffer             = "XCd229cc0000fd";
    x.property_insert_read                = "XCd229cc00009a";
    x.property_mem_write                  = "XCd229cc000033";
    x.property_destroy                    = "XCd229cc00013c";
    x.property_node_query_stat            = "XCd229cc0000b1";
    x.cstream_create                      = "XCd229cc000141";
    x.cstream_operate                     = "XCd229cc00008c";
    x.cstream_finish                      = "XCd229cc000025";
    x.cstream_destroy                     = "XCd229cc0000e3";
    return x;
    }(),
    [&] { avs_exports_t x = { 0 }; // sdvx cloud
    x.version_name                        = "SDVX Cloud/Beatstream";
    x.unique_check                        = "XCnbrep700013c";
    x.avs_fs_open                         = "XCnbrep700004e";
    x.avs_fs_close                        = "XCnbrep7000055";
    x.avs_fs_convert_path                 = "XCnbrep7000046";
    x.avs_fs_read                         = "XCnbrep7000051";
    x.avs_fs_lseek                        = "XCnbrep700004f";
    x.avs_fs_fstat                        = "XCnbrep7000062";
    x.avs_fs_lstat                        = "XCnbrep7000063";
    x.avs_fs_mount                        = "XCnbrep700004b";
    x.mdigest_create                      = "XCnbrep700013f";
    x.mdigest_update                      = "XCnbrep7000141";
    x.mdigest_finish                      = "XCnbrep7000142";
    x.mdigest_destroy                     = "XCnbrep7000143";
    x.property_read_query_memsize         = "XCnbrep70000b0";
    x.property_read_query_memsize_long    = "XCnbrep70000b1";
    x.property_create                     = "XCnbrep7000090";
    x.property_insert_read                = "XCnbrep7000094";
    x.property_mem_write                  = "XCnbrep70000b8";
    x.property_desc_to_buffer             = "XCnbrep7000092";
    x.property_destroy                    = "XCnbrep7000091";
    x.property_node_query_stat            = "XCnbrep70000c5";
    x.cstream_create                      = "XCnbrep7000130";
    x.cstream_operate                     = "XCnbrep7000132";
    x.cstream_finish                      = "XCnbrep7000133";
    x.cstream_destroy                     = "XCnbrep7000134";
    return x;
    }(),
    [&] { avs_exports_t x = { 0 }; // IIDX, "nbrep but different"
    x.version_name                        = "IIDX before 25";
    x.unique_check                        = NULL;
    x.avs_fs_open                         = "XCnbrep7000039";
    x.avs_fs_close                        = "XCnbrep7000040";
    x.avs_fs_convert_path                 = "XCnbrep7000031";
    x.avs_fs_read                         = "XCnbrep700003c";
    x.avs_fs_lseek                        = "XCnbrep700003a";
    x.avs_fs_fstat                        = "XCnbrep700004d";
    x.avs_fs_lstat                        = "XCnbrep700004e";
    x.avs_fs_mount                        = "XCnbrep7000036";
    x.mdigest_create                      = "XCnbrep7000133";
    x.mdigest_update                      = "XCnbrep7000135";
    x.mdigest_finish                      = "XCnbrep7000136";
    x.mdigest_destroy                     = "XCnbrep7000137";
    x.property_read_query_memsize         = "XCnbrep700009b";
    x.property_read_query_memsize_long    = "XCnbrep700009c";
    x.property_create                     = "XCnbrep700007b";
    x.property_insert_read                = "XCnbrep700007f";
    x.property_mem_write                  = "XCnbrep70000a3";
    x.property_desc_to_buffer             = "XCnbrep700007d";
    x.property_destroy                    = "XCnbrep700007c";
    x.property_node_query_stat            = "XCnbrep70000b0";
    x.cstream_create                      = "XCnbrep7000124";
    x.cstream_operate                     = "XCnbrep7000126";
    x.cstream_finish                      = "XCnbrep7000127";
    x.cstream_destroy                     = "XCnbrep7000128";
    return x;
    }(),
    [&] { avs_exports_t x = { 0 }; // avs 64 bit, pretty much
    x.version_name                        = "museca/IIDX 25+";
    x.unique_check                        = "XCgsqzn000013c";
    x.avs_fs_open                         = "XCgsqzn000004e";
    x.avs_fs_close                        = "XCgsqzn0000055";
    x.avs_fs_convert_path                 = "XCgsqzn0000046";
    x.avs_fs_read                         = "XCgsqzn0000051";
    x.avs_fs_lseek                        = "XCgsqzn000004f";
    x.avs_fs_fstat                        = "XCgsqzn0000062";
    x.avs_fs_lstat                        = "XCgsqzn0000063";
    x.avs_fs_mount                        = "XCgsqzn000004b";
    x.mdigest_create                      = "XCgsqzn000013f";
    x.mdigest_update                      = "XCgsqzn0000141";
    x.mdigest_finish                      = "XCgsqzn0000142";
    x.mdigest_destroy                     = "XCgsqzn0000143";
    x.property_read_query_memsize         = "XCgsqzn00000b0";
    x.property_read_query_memsize_long    = "XCgsqzn00000b1";
    x.property_create                     = "XCgsqzn0000090";
    x.property_insert_read                = "XCgsqzn0000094";
    x.property_mem_write                  = "XCgsqzn00000b8";
    x.property_desc_to_buffer             = "XCgsqzn0000092";
    x.property_destroy                    = "XCgsqzn0000091";
    x.property_node_query_stat            = "XCgsqzn00000c5";
    x.cstream_create                      = "XCgsqzn0000130";
    x.cstream_operate                     = "XCgsqzn0000132";
    x.cstream_finish                      = "XCgsqzn0000133";
    x.cstream_destroy                     = "XCgsqzn0000134";
    return x;
    }(),
};

#define AVS_FUNC_PTR(ret_type, name, ...) ret_type (* name )( __VA_ARGS__ );
FOREACH_AVS_FUNC(AVS_FUNC_PTR)

/*void* (*avs_fs_mount)(char* mountpoint, char* fsroot, char* fstype, int a5);
void* hook_avs_fs_mount(char* mountpoint, char* fsroot, char* fstype, int a5) {
    logf("Mounting %s at %s with type %s", fsroot, mountpoint, fstype);
    return avs_fs_mount(mountpoint, fsroot, fstype, a5);
}*/

#define TEST_HOOK_AND_APPLY(func) if (MH_CreateHookApi(dll_name, avs_exports[i]. ## func, hook_ ## func, (LPVOID*) &func) != MH_OK || func == NULL) continue
#define LOAD_FUNC(func) if( (func = (decltype(func))GetProcAddress(mod_handle, avs_exports[i]. ## func)) == NULL) continue
#define CHECK_UNIQUE(func) if( avs_exports[i]. ## func != NULL && GetProcAddress(mod_handle, avs_exports[i]. ## func) == NULL) continue

#define AVS_FUNC_LOAD(ret_type, name, ...) LOAD_FUNC(name);

bool init_avs(void) {
    bool success = false;

#ifdef _DEBUG
    for (int i = 0; i < lenof(avs_exports); i++) {
#define VERBOSE_EXPORT_CHECK(ret_type, name, ...) if(avs_exports[i]. ## name == NULL) logf("MISSING EXPORT %d: %s", i, #name);
        FOREACH_AVS_FUNC(VERBOSE_EXPORT_CHECK)
    }
#endif

    // presumably we don't load more than 1 unique avs dll.
    // Please don't be proven wrong
    LPCWSTR dll_name = NULL;
    HMODULE mod_handle = NULL;
    for (int i = 0; i < lenof(dll_names); i++) {
        mod_handle = GetModuleHandle(dll_names[i]);
        if (mod_handle != NULL) {
            dll_name = dll_names[i];
            break;
        }
    }

    if (mod_handle == NULL) {
        logf("Couldn't find AVS dll");
        return false;
    }

    for (int i = 0; i < lenof(avs_exports); i++) {
        // make sure this is the right DLL
        CHECK_UNIQUE(unique_check);

        // load all our imports, fail if any cannot be found
        FOREACH_AVS_FUNC(AVS_FUNC_LOAD)

        // apply hooks
        TEST_HOOK_AND_APPLY(avs_fs_open);
        TEST_HOOK_AND_APPLY(avs_fs_lstat);
        TEST_HOOK_AND_APPLY(avs_fs_mount);
        TEST_HOOK_AND_APPLY(avs_fs_convert_path);
        TEST_HOOK_AND_APPLY(avs_fs_read);

        success = true;
        logf("Detected dll: %s", avs_exports[i].version_name);
        break;
    }
    return success;
}

property_t prop_from_file_handle(AVS_FILE f) {
    void* prop_buffer = NULL;
    property_t prop = NULL;

    int flags = PROP_CREATE_FLAGS;
    auto memsize = property_read_query_memsize_long(avs_fs_read, f, NULL, NULL, NULL);
    if (memsize < 0) {
        // normal prop
        flags &= ~PROP_BIN_PLAIN_NODE_NAMES;

        avs_fs_lseek(f, 0, SEEK_SET);
        memsize = property_read_query_memsize(avs_fs_read, f, NULL, NULL);
        if (memsize < 0) {
            logf("Couldn't get memsize %08X (%s)", memsize, get_prop_error_str(memsize));
            goto FAIL;
        }
    }

    prop_buffer = malloc(memsize);
    prop = property_create(flags, prop_buffer, memsize);
    if (prop < 0) {
        // double cast to squash truncation warning
        logf("Couldn't create prop (%s)", get_prop_error_str((int32_t)(size_t)prop));
        goto FAIL;
    }

    avs_fs_lseek(f, 0, SEEK_SET);
    int ret = property_insert_read(prop, 0, avs_fs_read, f);
    avs_fs_close(f);

    if (ret < 0) {
        logf("Couldn't read prop (%s)", get_prop_error_str(ret));
        goto FAIL;
    }

    return prop;

FAIL:
    avs_fs_close(f);
    if (prop)
        property_destroy(prop);
    if (prop_buffer)
        free(prop_buffer);
    return NULL;
}

property_t prop_from_file_path(string const&path) {
    AVS_FILE f = avs_fs_open(path.c_str(), 1, 420);
    if (f < 0) {
        logf("Couldn't open prop");
        return NULL;
    }

    return prop_from_file_handle(f);
}

char* prop_to_xml_string(property_t prop, rapidxml::xml_document<>& allocator) {
    node_size dummy = { 0 };

    auto prop_size = property_node_query_stat(prop, NULL, &dummy);
    char* xml = allocator.allocate_string(NULL, prop_size);

    auto written = property_mem_write(prop, xml, prop_size);
    if (written > 0) {
        xml[written] = '\0';
    }
    else {
        xml[0] = '\0';
        logf("property_mem_write failed (%s)", get_prop_error_str(written));
    }

    return xml;
}

char* avs_file_to_string(AVS_FILE f, rapidxml::xml_document<>& allocator) {
    avs_stat stat = {0};
    avs_fs_fstat(f, &stat);
    char* ret = allocator.allocate_string(NULL, stat.filesize + 1);
    avs_fs_read(f, ret, stat.filesize);
    ret[stat.filesize] = '\0';
    return ret;
}

bool is_binary_prop(AVS_FILE f) {
    avs_fs_lseek(f, 0, SEEK_SET);
    unsigned char head;
    auto read = avs_fs_read(f, &head, 1);
    bool ret = (read == 1) && head == 0xA0;
    avs_fs_lseek(f, 0, SEEK_SET);
    //logf("detected binary: %s (read %d byte %02x)", ret ? "true": "false", read, head&0xff);
    return ret;
}

bool rapidxml_from_avs_filepath(
    string const& path,
    rapidxml::xml_document<>& doc,
    rapidxml::xml_document<>& doc_to_allocate_with
) {
    AVS_FILE f = avs_fs_open(path.c_str(), 1, 420);
    if (f < 0) {
        logf("Couldn't open prop");
        return false;
    }

    // if it's not binary, don't even bother parsing with avs
    char* xml = NULL;
    if (is_binary_prop(f)) {
        auto prop = prop_from_file_handle(f);
        if (!prop)
            return false;

        xml = prop_to_xml_string(prop, doc_to_allocate_with);
        prop_free(prop);
    }
    else {
        xml = avs_file_to_string(f, doc_to_allocate_with);
    }
    avs_fs_close(f);

    /*FILE* fff;
    fopen_s(&fff, "hmmm.xml", "wb");
    fwrite(xml_owned, 1, strlen(xml_owned), fff);
    fclose(fff);*/

    try {
        // parse_declaration_node: to get the header <?xml version="1.0" encoding="shift-jis"?>
        doc.parse<rapidxml::parse_declaration_node | rapidxml::parse_no_utf8>(xml);
    } catch (const rapidxml::parse_error& e) {
        logf("Couldn't parse xml (%s byte %d)", e.what(), (int)(e.where<char>() - xml));
        return false;
    }

    return true;
}

/*char* prop_xml_string_from_prop(property_t prop) {
    auto prop_size = property_node_query_stat(prop, NULL, NULL);
    char* xml = (char*)calloc(0, prop_size);
    property_mem_write(prop, xml, prop_size);
    return xml;
}

char* prop_xml_string_from_file(string const&path) {
    auto prop = prop_from_file(path);
    if (!prop)
        return NULL;

    auto xml = prop_xml_string_from_prop(prop);
    prop_free(prop);
    return xml;
}*/

void prop_free(property_t prop) {
    if (!prop)
        return;
    auto buffer = property_desc_to_buffer(prop);
    property_destroy(prop);
    free(buffer);
}

string md5_sum(const char* str) {
    uint8_t sum[MD5_LEN];
    char sum_str[MD5_LEN*2 + 1];
    auto digest = mdigest_create(MD5);
    mdigest_update(digest, str, (int)strlen(str));
    mdigest_finish(digest, sum, MD5_LEN);
    mdigest_destroy(digest);
    for (int i = 0; i < MD5_LEN; i++) {
        snprintf(sum_str + 2 * i, 3, "%02x", sum[i]);
    }
    return sum_str;
}

unsigned char* lz_compress(unsigned char* input, size_t length, size_t *compressed_length) {
    auto compressor = cstream_create(AVS_COMPRESS_AVSLZ);
    if (!compressor) {
        logf("Couldn't create");
        return NULL;
    }
    compressor->input_buffer = input;
    compressor->input_size = (uint32_t)length;
    // worst case, for every 8 bytes there will be an extra flag byte
    auto to_add = max(length / 8, 1);
    auto compress_size = length + to_add;
    auto compress_buffer = (unsigned char*)malloc(compress_size);
    compressor->output_buffer = compress_buffer;
    compressor->output_size = (uint32_t)compress_size;

    bool ret;
    ret = cstream_operate(compressor);
    if (!ret && !compressor->input_size) {
        compressor->input_buffer = NULL;
        compressor->input_size = -1;
        ret = cstream_operate(compressor);
    }
    if (!ret) {
        logf("Couldn't operate");
        return NULL;
    }
    if (cstream_finish(compressor)) {
        logf("Couldn't finish");
        return NULL;
    }
    *compressed_length = compress_size - compressor->output_size;
    cstream_destroy(compressor);
    return compress_buffer;
}

typedef struct {
    uint32_t code;
    char* msg;
} prop_error_info_t;

const prop_error_info_t prop_error_list[73] = {
    { 0x80092000, "invalid type" },
    { 0x80092001, "type cannot use as array" },
    { 0x80092002, "invalid" },
    { 0x80092003, "too large data size" },
    { 0x80092004, "too small buffer size" },
    { 0x80092005, "passcode 0 is not allowed" },
    { 0x80092040, "invalid node name" },
    { 0x80092041, "invalid attribute name" },
    { 0x80092042, "reserved attribute name" },
    { 0x80092043, "cannot find node/attribute" },
    { 0x80092080, "cannot allocate node" },
    { 0x80092081, "cannot allocate node value" },
    { 0x80092082, "cannot allocate mdigest for finger-print" },
    { 0x80092083, "cannot allocate nodename" },
    { 0x800920C0, "node type differs" },
    { 0x800920C1, "node type is VOID" },
    { 0x800920C2, "node is array" },
    { 0x800920C3, "node is not array" },
    { 0x80092100, "node is create-disabled" },
    { 0x80092101, "node is read-disabled" },
    { 0x80092102, "node is write-disabled" },
    { 0x80092103, "flag is already locked" },
    { 0x80092104, "passcode differs" },
    { 0x80092105, "insert_read() is applied to attribute" },
    { 0x80092106, "part_write() is applied to attribute" },
    { 0x80092107, "MODE_EXTEND flag differs" },
    { 0x80092140, "root node already exists" },
    { 0x80092141, "attribute cannot have children" },
    { 0x80092142, "node/attribute already exists" },
    { 0x80092143, "number of nodes exceeds 65535" },
    { 0x80092144, "cannot interpret as number" },
    { 0x80092145, "property is empty" },
    { 0x80092180, "I/O error" },
    { 0x80092181, "unexpected EOF" },
    { 0x80092182, "unknown format" },
    { 0x800921C0, "broken magic" },
    { 0x800921C1, "broken metadata" },
    { 0x800921C2, "broken databody" },
    { 0x800921C3, "invalid type" },
    { 0x800921C4, "too large data size" },
    { 0x800921C5, "too long node/attribute name" },
    { 0x800921C6, "attribute name is too long" },
    { 0x800921C7, "node/attribute already exists" },
    { 0x80092200, "invalid encoding " },
    { 0x80092201, "invalid XML token" },
    { 0x80092202, "XML syntax error" },
    { 0x80092203, "STag/ETag mismatch" },
    { 0x80092204, "too large node data" },
    { 0x80092205, "too deep node tree" },
    { 0x80092206, "invalid type" },
    { 0x80092207, "invalid size" },
    { 0x80092208, "invalid count" },
    { 0x80092209, "invalid value" },
    { 0x8009220A, "invalid node name" },
    { 0x8009220B, "invalid attribute name" },
    { 0x8009220C, "reserved attribute name" },
    { 0x8009220D, "node/attribute already exists" },
    { 0x8009220E, "too many elements in node data" },
    { 0x80092240, "JSON syntax error" },
    { 0x80092241, "invalid JSON literal" },
    { 0x80092242, "invalid JSON number" },
    { 0x80092243, "invalid JSON string" },
    { 0x80092244, "invalid JSON object name" },
    { 0x80092245, "object name already exists" },
    { 0x80092246, "too long JSON object name" },
    { 0x80092247, "too deep JSON object/array nesting" },
    { 0x80092248, "cannot convert JSON array to property" },
    { 0x80092249, "cannot convert empty JSON object to property" },
    { 0x8009224A, "root node already exists" },
    { 0x8009224B, "cannot convert root node to TYPE_ARRAY" },
    { 0x8009224C, "name represents reserved attribute" },
    { 0x80092280, "finger-print differs" },
    { 0x800922C0, "operation is not supported" },
};

const char* get_prop_error_str(int32_t code) {
    static char ret[64];
    for (int i = 0; i < lenof(prop_error_list); i++) {
        if (prop_error_list[i].code == code)
            return prop_error_list[i].msg;
    }
    snprintf(ret, sizeof(ret), "unknown (%d)", code);
    return ret;
}

char* prop_data_to_str(int type, void* data) {
    static char ret[64];

    type &= 63;

    switch (type) {
        case PROP_TYPE_node:
            return "none - node element";
        case PROP_TYPE_str:
        case PROP_TYPE_attr:
            snprintf(ret, sizeof(ret), "%s", (char*)data);
            return ret;
        case PROP_TYPE_s8:
        case PROP_TYPE_u8:
        case PROP_TYPE_s16:
        case PROP_TYPE_u16:
        case PROP_TYPE_s32:
        case PROP_TYPE_u32:
        case PROP_TYPE_s64:
        case PROP_TYPE_u64:
        case PROP_TYPE_bin:
        case PROP_TYPE_ip4:
        case PROP_TYPE_time:
        case PROP_TYPE_float:
        case PROP_TYPE_double:
        case PROP_TYPE_2s8:
        case PROP_TYPE_2u8:
        case PROP_TYPE_2s16:
        case PROP_TYPE_2u16:
        case PROP_TYPE_2s32:
        case PROP_TYPE_2u32:
        case PROP_TYPE_2s64:
        case PROP_TYPE_2u64:
        case PROP_TYPE_2f:
        case PROP_TYPE_2d:
        case PROP_TYPE_3s8:
        case PROP_TYPE_3u8:
        case PROP_TYPE_3s16:
        case PROP_TYPE_3u16:
        case PROP_TYPE_3s32:
        case PROP_TYPE_3u32:
        case PROP_TYPE_3s64:
        case PROP_TYPE_3u64:
        case PROP_TYPE_3f:
        case PROP_TYPE_3d:
        case PROP_TYPE_4s8:
        case PROP_TYPE_4u8:
        case PROP_TYPE_4s16:
        case PROP_TYPE_4u16:
        case PROP_TYPE_4s32:
        case PROP_TYPE_4u32:
        case PROP_TYPE_4s64:
        case PROP_TYPE_4u64:
        case PROP_TYPE_4f:
        case PROP_TYPE_4d:
        case PROP_TYPE_attr_and_node:
        case PROP_TYPE_vs8:
        case PROP_TYPE_vu8:
        case PROP_TYPE_vs16:
        case PROP_TYPE_vu16:
        case PROP_TYPE_bool:
        case PROP_TYPE_2b:
        case PROP_TYPE_3b:
        case PROP_TYPE_4b:
        case PROP_TYPE_vb:
            snprintf(ret, sizeof(ret), "STR REP NOT IMPLEMENTED (%d)", type);
            return ret;
        default:
            return "UNKNOWN";
    }
}
