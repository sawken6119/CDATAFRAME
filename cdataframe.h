

int insert_value(COLUMN* col, const void* value, int index);

void delete_column(COLUMN **col);

void print_col(COLUMN* col);

int occurences(void* x, COLUMN *col);

void * valeur_presente(int x, COLUMN *col);

int superieurs(void* x, COLUMN *col);

int inferieures(void* x, COLUMN *col);

int egales(void* x, COLUMN *col);

void remplissage_utilisateur(COLUMN **CDataframe, int nombre_de_colonnes);

void remplissage_dur(COLUMN **CDataframe, int nombre_de_colonnes);

void print_DataFrame(COLUMN **CDataframe, int nombre_de_colonnes);

void print_partial_row_data(COLUMN** CDataframe, int nombre_de_colonnes, int start_index, int end_index);

void print_partial_column_data(COLUMN **CDataframe, int nombre_de_colonnes, int start_index, int end_index);

void add_row(COLUMN** CDataframe, int nombre_de_colonnes, void** values);

void delete_row(COLUMN** CDataframe, int nombre_de_colonnes, int index);

void add_column(COLUMN*** CDataframe, int* nombre_de_colonnes, char* title, int type, void* values, int size);

void delete_column_CDataframe(COLUMN*** CDataframe, int* nombre_de_colonnes, int index);

void rename_column(COLUMN** CDataframe, int nombre_de_colonnes, int index, char* new_title);

int value_exists_in_column(COLUMN* column, void* value);

int value_exists_in_CDataframe(COLUMN** CDataframe, int nombre_de_colonnes, void* value);

size_t get_type_size(int type);

void replace_value(COLUMN* col, int row_index, int new_value)

#endif //CDATAFRAME_CDATAFRAME_H
