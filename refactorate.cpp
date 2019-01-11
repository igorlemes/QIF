vector< vector < long double > > innerRefactorate(vector< vector < long double > > matrix){
	vector<int> columns = equalColumns(matrix);
	vector< vector < long double > >  refactorated(matrix.size(), vector < long double >(sizeColumns(columns), 0) );
	int index = 0;
	for (size_t i = 0; i < matrix[0].size(); i++) {
		if(positionWanted(columns, i) != -1){
			for (size_t j = 0; j <  matrix.size(); j++) {
				refactorated[index][j] = matrix[positionWanted(columns, i)][j];
				index++;
			}
		}
	}
}

vector < long double > outerRefactorate(vector< vector < long double > > matrix, vector < long double > outer){
	
}

int positionWanted(vector<int> columns, int wanted){
	for (size_t i = 0; i < columns.size(); i++) {
		if(columns[i] == wanted) return i;
	}
	return -1;
}

int sizeColumns(vector<int> columns){
	int size = columns.size();
	for(int i = 0; i <  columns.size(); i++){
		for(int j = 0; j < columns.size(); j++){
			if(i != j){
				if(columns[i] == columns[j]) size--;
			}
		}
	}
	return size;
}
vector<int> equalColumns(vector< vector < long double > > matrix){
	vector<int> columns(matrix[0].size(), -1);
	int aux;
	for(int i = 0; i < matrix[0].size(); i++){
		for(int j = 0; j < matrix[0].size(); j++){
			aux = 0;
			if(columns[j] == -1){
				for(int k = 0; k < matrix.size(); k++){
					if(matrix[k][i] == matrix[k][j])	aux++;
				}
				if(aux == matrix.size()){
					columns[j] = i;
				}
			}
		}
	}
	return columns;
}
