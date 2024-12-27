import configparser

def update_bc_decls( group: str , items: list[tuple[str,str]] ) -> tuple[str,str]:
    this_bc_decl = ""
    this_bc_def = ""
    for item in items:
        item_name = f"bc_{ group }_{ item[0] }"
        item_value = item[1]
        this_bc_decl += f"    extern const std::string { item_name };\n    extern const std::wstring { item_name }_w;\n"
        this_bc_def += f"const std::string rena::builtin::{ item_name } = \"{ item_value }\";\nconst std::wstring rena::builtin::{ item_name }_w = L\"{ item_value }\";\n"
    return this_bc_decl , this_bc_def

def main():
    cp = configparser.ConfigParser()
    cp.read( "./data/update_box_chars.cfg" , encoding = 'utf-8' )
    target_header = cp.get( "target" , "header" )
    target_source = cp.get( "target" , "source" )
    source_header = cp.get( "source" , "header" )
    source_source = cp.get( "source" , "source" )

    i_bc_decls = ""
    i_bc_defs = ""

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
        bc_decl , bc_def = update_bc_decls( group , cp.items( group ) )
        i_bc_decls += bc_decl
        i_bc_defs += bc_def

    with open( source_header , 'r' ) as rFile:
        header_code = rFile.read()

    with open( source_source , 'r' ) as rFile:
        source_code = rFile.read()

    header_code = header_code.replace( "@INSERT_BC_DECLS@" , i_bc_decls[:-1] )
    source_code = source_code.replace( "@INSERT_BC_DEFS@" , i_bc_defs[:-1] )

    with open( target_header , 'w' ) as wFile:
        wFile.write( header_code )

    with open( target_source , 'w' ) as wFile:
        wFile.write( source_code )

if __name__ == "__main__":
    main()
