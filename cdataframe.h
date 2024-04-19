int insert_value(COLUMN* col, int value);

void delete_column(COLUMN *col);

void print_col(COLUMN* col);

int occurences(int x, COLUMN *col);

int valeur_presente(int x, COLUMN *col);

int superieurs(int x, COLUMN *col);

int inferieures(int x, COLUMN *col);

int egales(int x, COLUMN *col);

void remplissage_dur(COLUMN **CDataframe, int nombre_de_colonnes);

void remplissage_utilisateur(COLUMN **CDataframe, int nombre_de_colonnes);

void print_DataFrame(COLUMN **CDataframe, int nombre_de_colonnes);

void print_partial_data(COLUMN** CDataframe, int nombre_de_colonnes, int start_index, int end_index);

void add_column(COLUMN*** CDataframe, int* nombre_de_colonnes, char* title, DataType type);

void delete_row(COLUMN* col, int index, int type);

size_t get_type_size(int type);

void add_row(COLUMN** CDataframe, int nombre_de_colonnes, void** values, int* types);

void delete_colum(COLUMN*** CDataframe, int* nombre_de_colonnes, int index);

void rename_column(COLUMN* col, char* new_title);

int value_exist(COLUMN* col, int x);

int acces(COLUMN* col, int row_index);

void replace_value(COLUMN* col, int row_index, int new_value);

void print_column_names(COLUMN** CDataframe, int nombre_de_colonnes);

int get_row_coun(COLUMN* col);

int get_column_count(int nombre_de_colonnes);

int count_cells_equal_to(COLUMN** CDataframe, int nombre_de_colonnes, int x);

int count_cells_greater_than(COLUMN** CDataframe, int nombre_de_colonnes, int x);

int count_cells_less_than(COLUMN** CDataframe, int nombre_de_colonnes, int x);
