/*
    File: matrix.cpp
    Author: Natalie Buchoff
    Section: CMSC 313, MW 10-11:15am
    Description: this code makes a matrix class to make an object that does matric functions in c++
*/
#include <iostream>
using namespace std;

class Matrix{
  public:
    //matrix constructor
    Matrix(int rows = 0, int cols = 0){
        // initializes m_rows and m_cols, to 0 if given value is not valid
        if(rows >= 0 && cols != 0){m_rows = rows;}
        else{m_rows = 0;}
        if(cols >= 0 && rows != 0){m_cols = cols;}
        else{m_cols = 0;}

        //initialize m_mat
        if(rows == 0 or cols == 0){
            m_mat = nullptr;
        }else{
            m_mat = nullptr; //initialize m_mat before use
            m_mat = Make2dArray(m_rows, m_cols);
        }
    }
    //destructor
    ~Matrix(){
        clear();
    }
    void clear(){
        if(m_mat != nullptr){
            for(int i = 0; i < m_rows; i++){
                if(m_mat[i] != nullptr){
                    delete m_mat[i];    //delete each row
                    m_mat[i] = nullptr;
                }
            }
            delete[] m_mat;
            m_mat = nullptr;
        }
        m_rows = 0;
        m_cols = 0;
    }
    //function to add matrices
    void AddWithMatrix(Matrix &otherMat){
        if(m_rows != otherMat.m_rows || m_cols != otherMat.m_cols){   
            cout << "Matrix Addition Failed: Incompatible matrix dimensions\n";
            return;
        }else if(m_mat && otherMat.m_mat){
            for(int i = 0; i < m_rows; i++){
                for(int j = 0; j < m_cols; j++){
                    m_mat[i][j] += otherMat.m_mat[i][j];
                }
            }
        }
    }
    // fill matrix
    void FillMatrix(){
        cout << "Creating a new matrix...\n";
        int num = 0;
        for(int i = 0; i < m_rows; i++){
            for(int j = 0; j < m_cols; j++){
                cout << "Enter an int for row " << i + 1 << ", column " << j + 1 << ": ";
                cin >> num;
                m_mat[i][j] = num;
            }
        }
    }
    //multiplication of matrices
    void MultiplyMatrices(Matrix& mat){
        if(m_rows != mat.m_cols){  //AB != BA, only count it if it is this
            cout << "Matrix Multiplication Failed: incompatible matrix dimensions\n";
            return;
        }
        // do the multiplication
        int ** newMat = Make2dArray(m_rows, m_rows);  //resulting array dimensions are rows of main matrix
        for(int i = 0; i < m_rows; i++){
            for(int j = 0; j < m_rows; j++){
                for(int k = 0; k < m_cols; k++){
                    newMat[i][j] += m_mat[i][k] * mat.m_mat[k][j];
                }
            }
        }
        clear(); //clear since we're making the pointer to this point to the new matrix and don't want to have memory leak
        m_rows = mat.m_cols;
        m_cols = m_rows;
        m_mat = newMat;
    }
    //scalar muliplication on matrix
    void ScaleMatrix(int scalar){
        for(int i = 0; i < m_rows; i++){
            for(int j = 0; j < m_cols; j++){
                m_mat[i][j] *= scalar;  //muliply each element by the scalar
            }
        }
    }
    //transpose matrix
    void TransposeMatrix(){
        int newRows = m_cols;
        int newCols = m_rows;
        int ** newMat = Make2dArray(newRows, newCols);
        for(int i = 0; i < newRows; i++){
            for(int j = 0 ; j < newCols; j++){
                newMat[i][j] = m_mat[j][i];
            }
        }
        clear();
        m_rows = newRows;
        m_cols = newCols;
        m_mat = newMat;
    }
    //display the matrix
    void DisplayMatrix(){
        if(m_mat){ //if m_mat is not nullptr
            for(int i = 0; i < m_rows; i++){
                cout << "| ";
                for(int j = 0; j < m_cols; j++){
                    cout << m_mat[i][j] << ' ';
                }
                cout << "|\n";
            }
        }
    }
    //copy constructor
    Matrix(const Matrix& source){
        m_rows = source.m_rows;
        m_cols = source.m_cols;
        m_mat = nullptr;
        if(source.m_mat){
            m_mat = new int*[m_rows];
            for(int i = 0; i < m_rows; i++){
                m_mat[i] = new int[m_cols];   //make 2d array structure
                for(int j = 0; j < m_cols; j++){
                    m_mat[i][j] = source.m_mat[i][j]; //copy values
                }
            }
        }
    }
    // assignment operator
    Matrix& operator=(const Matrix& source){
        if(this != &source){
            clear();    //deallocate old
            m_rows = source.m_rows; //copy new
            m_cols = source.m_cols;
            m_mat = nullptr;
            if(source.m_mat){
                m_mat = new int*[m_rows];
                for(int i = 0; i < m_rows; i++){
                    m_mat[i] = new int[m_cols];   //make 2d array structure
                    for(int j = 0; j < m_cols; j++){
                        m_mat[i][j] = source.m_mat[i][j]; //copy values
                    }
                }
            }
        }
        return *this;
    }
  private:
    //make empty 2d array
    int ** Make2dArray(int rows, int cols){
        int ** arr = new int*[rows];
        for(int i = 0; i < rows; i++){
            arr[i] = new int[cols];   //make 2d array structure
            for(int j = 0; j < cols; j++){
                arr[i][j] = 0; //initialize with zeros
            }
        }
        return arr;
    }
    int m_rows;
    int m_cols;
    int ** m_mat;
};

int main(){
    // matrices A, B, and C here should be made to represent the corresponding matrices in HW#8
    Matrix A = Matrix(2, 2);
    A.FillMatrix(); //you need to put in these values manually, sorry
    A.DisplayMatrix();

    Matrix B = Matrix(2, 3);
    B.FillMatrix();
    B.DisplayMatrix();

    Matrix C = Matrix(2, 3);
    C.FillMatrix();
    C.DisplayMatrix();

    B.ScaleMatrix(3);   //matrix operations begin
    C.TransposeMatrix();
    B.MultiplyMatrices(C);
    A.AddWithMatrix(B);
    Matrix D = A;
    cout << "\nMatrix D:\n";
    D.DisplayMatrix();
}