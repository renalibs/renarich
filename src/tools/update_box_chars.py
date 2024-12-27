import configparser

bc_index = 0
bc_item_name_index_table = {
    "h": 0 ,
    "v": 1 ,
    "dr": 2 ,
    "dl": 3 ,
    "ur": 4 ,
    "ul": 5 ,
    "vr": 6 ,
    "vl": 7 ,
    "dh": 8 ,
    "uh": 9 ,
    "vh": 10
}

def update_bc_index_macros( group: str ) -> str:
    global bc_index
    this_bc_index_macro = f"#define BC_G_{ group.upper() } { bc_index }\n"
    bc_index = bc_index + 1
    return this_bc_index_macro

def update_bc_decls() -> str:
    global bc_index
    return f"    extern const std::string bc_table[{ bc_index }][11];\n"

def update_bc_w_decls() -> str:
    global bc_index
    return f"    extern const std::wstring bc_w_table[{ bc_index }][11];\n"

def update_bc_defs( items: list[tuple[str,str]] ) -> str:
    this_bc_def = "    { "
    items = sorted( items , key = lambda x: bc_item_name_index_table.get( x[0] ) )
    need_comma = False
    for item in items:
        if not need_comma:
            this_bc_def += f"\"{ item[1] }\" "
            need_comma = True
        else:
            this_bc_def += f", \"{ item[1] }\" "
    this_bc_def += " } ,\n"
    return this_bc_def

def update_bc_w_defs( items: list[tuple[str,str]] ) -> str:
    this_bc_w_def = "    { "
    items = sorted( items , key = lambda x: bc_item_name_index_table.get( x[0] ) )
    need_comma = False
    for item in items:
        if not need_comma:
            this_bc_w_def += f"L\"{ item[1] }\" "
            need_comma = True
        else:
            this_bc_w_def += f", L\"{ item[1] }\" "
    this_bc_w_def += " } ,\n"
    return this_bc_w_def

def main():
    cp = configparser.ConfigParser()
    cp.read( "./data/update_box_chars.cfg" , encoding = 'utf-8' )
    target_header = cp.get( "target" , "header" )
    target_source = cp.get( "target" , "source" )
    source_header = cp.get( "source" , "header" )
    source_source = cp.get( "source" , "source" )

    i_bc_index_macros = ""
    i_bc_decls = ""
    i_bc_w_decls = ""
    i_bc_defs = ""
    i_bc_w_defs = ""

    print( "Updating config:" )
    print( f" - { source_header } -> { target_header }" )
    print( f" - { source_source } -> { target_source }" )

    bdc_group_list = []
    print( "Found following box drawing character groups:" )
    for section in cp:
        if section not in [ "DEFAULT" , "target" , "source" ]:
            bdc_group_list.append( section )
            print( f" - { section }" )

    for group in bdc_group_list:
        print( f"Entering group: { group }" )
        i_bc_index_macros += update_bc_index_macros( group )
        i_bc_defs += update_bc_defs( cp.items( group ) )
        i_bc_w_defs += update_bc_w_defs( cp.items( group ) )

    i_bc_defs += "};\n"
    i_bc_w_defs += "};\n"
    i_bc_defs = f"const std::string rena::builtin::bc_table[{ bc_index }][11] = {{\n" + i_bc_defs
    i_bc_w_defs = f"const std::wstring rena::builtin::bc_w_table[{ bc_index }][11] = {{\n" + i_bc_w_defs

    i_bc_decls = update_bc_decls()
    i_bc_w_decls = update_bc_w_decls()

    with open( source_header , 'r' ) as rFile:
        header_code = rFile.read()

    with open( source_source , 'r' ) as rFile:
        source_code = rFile.read()

    header_code = header_code.replace( "@INSERT_BC_INDEX_MACROS@" , i_bc_index_macros[:-1] )
    header_code = header_code.replace( "@INSERT_BC_DECLS@" , i_bc_decls[:-1] )
    header_code = header_code.replace( "@INSERT_BC_W_DECLS@" , i_bc_w_decls[:-1] )
    source_code = source_code.replace( "@INSERT_BC_DEFS@" , i_bc_defs[:-1] )
    source_code = source_code.replace( "@INSERT_BC_W_DEFS@" , i_bc_w_defs[:-1] )

    with open( target_header , 'w' ) as wFile:
        wFile.write( header_code )

    with open( target_source , 'w' ) as wFile:
        wFile.write( source_code )

if __name__ == "__main__":
    main()
