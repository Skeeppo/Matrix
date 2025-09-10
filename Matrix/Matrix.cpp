#include <iostream>
#include <string>

template<class T> 
class Matrix
{
    static_assert(std::is_arithmetic_v<T>,"hui");
private:
    //Инициальзация размера матрицы и одного массива, содержащего элементы Т
    int m_range;
    T* m_matrix = nullptr;


    //Класс, являющийся матрицей-строкой, необходимы для поиска элемента в матрице
    class Row
    {
        T* i_str;
        int m_rowSize;
        
    public:
        Row(T* data, int size) : i_str(data), m_rowSize(size){};
    
        T& operator[](int inp_j)
        {       
            if (inp_j > m_rowSize - 1 || inp_j < 0)
            {
                throw std::out_of_range("Out of range");
            }
            return i_str[inp_j];
        }    
        const T& operator[](int inp_j) const
        {
            if (inp_j > m_rowSize - 1 || inp_j < 0)
            {
                throw std::out_of_range("Out of range");
            }
            return i_str[inp_j];
        }
        
    };

    class ConstRow
    {
        const T* i_str;
        int m_rowSize;

    public:
        ConstRow(const T* data, int size) : i_str(data), m_rowSize(size) {};

        const T& operator[](int inp_j) const
        {
            if (inp_j > m_rowSize - 1 || inp_j < 0)
            {
                throw std::out_of_range("Out of range");
            }
            return i_str[inp_j];
        }

    };
    
public:
    Row operator[](int inp_i)
    {
        if (inp_i > m_range - 1  || inp_i < 0)
        {
            throw std::out_of_range("Out of range");
        }
        return Row{m_matrix + inp_i*m_range, m_range};
    }

    const ConstRow operator[](int inp_i) const
    {
        if (inp_i > m_range - 1 || inp_i < 0)
        {
            throw std::out_of_range("Out of range");
        }
        return ConstRow{ m_matrix + inp_i * m_range, m_range };
    }
    
    //Метод, выводящий элементы матрицы в нормальном виде(квадратиком)
    void show()
    {
        if (m_matrix == nullptr) 
        {
            std::cout << "Nahui ty mne pustuyu matritsu peredal";
            return;
        }
        for (int i = 0; i < m_range*m_range; i++)
        {
            if (i % m_range == 0 && i != 0)
            {
                std::cout << std::endl;
            }
            std::cout << m_matrix[i] << " ";

        }
        std::cout << std::endl;
        std::cout << std::endl;
    }

    //Метод сложения двух матриц
    Matrix operator+(const Matrix& matrix)
    {
        if (matrix.m_range != m_range)
        {
            throw std::out_of_range("razniy range");
        }
        Matrix<T> newMatrix(m_range, 0);
        for (int i = 0; i < m_range*m_range; i++)
        {
            newMatrix.m_matrix[i] = m_matrix[i] + matrix.m_matrix[i];
        }
        return newMatrix;
    }

    //Метод увеличения одной матрицы
    Matrix& operator+=(const Matrix& matrix)
    {
        
        if (matrix.m_range != m_range)
        {
            throw std::out_of_range("razniy range");
        }
        for (int i = 0; i < m_range * m_range; i++)
        {
            m_matrix[i] = m_matrix[i] + matrix.m_matrix[i];
        }
        return *this;
    }   

    Matrix operator*(const Matrix& matrix)
    {

        if (matrix.m_range != m_range)
        {
            throw std::out_of_range("razniy range");
        }
        Matrix<T> newMatrix(m_range, 0);
        for (int i = 0; i < m_range; i++)
        {
            for (int j = 0; j < m_range; j++)
            {
                for (int k = 0; k < m_range; k++)
                {
                    newMatrix[i][j] += (*this)[i][k] * matrix[k][j];
                }
              
            }
        }
        return newMatrix;
    }

    Matrix& operator*=(const Matrix& matrix)
    {

        if (matrix.m_range != m_range)
        {
            throw std::out_of_range("razniy range");
        }
        Matrix<T> newMatrix(m_range, 0);
        for (int i = 0; i < m_range; i++)
        {
            for (int j = 0; j < m_range; j++)
            {
                for (int k = 0; k < m_range; k++)
                {
                    newMatrix[i][j] += (*this)[i][k] * matrix[k][j];
                }

            }
        }
        *this = newMatrix;
        return *this;
    }

    Matrix& operator*=(T value) 
    {
               
        for (int i = 0; i < m_range*m_range; i++)
        {
            m_matrix[i] *= value;
        }
        return *this;
    }

    Matrix operator*(T value) const
    {
        Matrix<T> newMatrix(m_range, 1);
        for (int i = 0; i < m_range * m_range; i++)
        {
            newMatrix.m_matrix[i] = m_matrix[i] * value;
        }
        return newMatrix;
    }

    //Оператор копирования
    Matrix& operator=(const Matrix& matrix)
    {
        
        if (this != &matrix)
        {
            if (matrix.m_range != m_range)
            {
                delete[] m_matrix;
                m_matrix = new T[matrix.m_range * matrix.m_range];
                m_range = matrix.m_range;
            }
            for (int i = 0; i < m_range * m_range; i++)
            {
                m_matrix[i] = matrix.m_matrix[i];
            }
            
        }
        return *this;
    }

    //Оператор перемещения
    Matrix& operator=(Matrix&& matrix) noexcept(true)
    {
        if (matrix.m_matrix == nullptr)
        {
            throw std::runtime_error("Hui");
        }
        if (this == &matrix)
        {
            return *this;
        }
        std::swap(m_matrix, matrix.m_matrix);
        m_range = matrix.m_range;
        return *this;
        
    }

    bool operator!=(Matrix& matrix) 
    {
        if (matrix.m_matrix == nullptr)
        {
            throw std::runtime_error("Hui");
        }
        if (this == &matrix)
        {
            return false;
        }
        for (int i = 0; i < matrix.m_range * matrix.m_range; i++)
        {
            if (matrix.m_matrix[i] != m_matrix[i])
            {
                return true;
            }
        }
        return false;

    }

    bool operator==(Matrix& matrix)
    {
        if (matrix.m_matrix == nullptr)
        {
            throw std::runtime_error("Hui");
        }
        if (this == &matrix)
        {
            return true;
        }
        for (int i = 0; i < matrix.m_range * matrix.m_range; i++)
        {
            if (matrix.m_matrix[i] != m_matrix[i])
            {
                return false;
            }
        }
        return true;

    }

    bool operator!=(Matrix&& matrix)
    {
        if (matrix.m_matrix == nullptr)
        {
            throw std::runtime_error("Hui");
        }
        if (this == &matrix)
        {
            return false;
        }
        return *this != matrix;

    }

    bool operator==(Matrix&& matrix)
    {
        if (matrix.m_matrix == nullptr)
        {
            throw std::runtime_error("Hui");
        }
        if (this == &matrix)
        {
            return false;
        }
        return *this == matrix;
    }

    //Метод возвращения размеры матрицы
    int range()const
    {
        return m_range;
    }

    //Конструктор по умолчанию(1 элемент, значение 0)
    Matrix() : m_range(1), m_matrix(new T[1])
    {
        m_matrix[0] = 0;
    }

    //Конструктор по размеру и массиву Т
    Matrix(int size, T* arr): m_range(size), m_matrix(new T[size * size])
    {
        if (arr == nullptr)
        {
            throw std::out_of_range("U tebya massiva net, dolboeb, ne ebi mne mozgi");
        }
        for (int i = 0; i < m_range*m_range; i++)
        {
            m_matrix[i] = arr[i];
        }
    }


    //Конструктор по размеру, заполняющий всю матрицу одним элементом T(единичная матрица, нулевая и пр.)
    Matrix(int size, T value) : m_range(size), m_matrix(new T[size*size])
    {
        for (int i = 0; i < m_range*m_range; i++)
        {
            m_matrix[i] = value;
        }
    }

    //Конструктор копирования
    Matrix(const Matrix& matrix) : m_range(matrix.m_range), m_matrix(new T[matrix.m_range * matrix.m_range])
    {
        if (matrix.m_matrix == nullptr)
        {
            throw std::runtime_error("Hui");
        }
        for (int i = 0; i < m_range * m_range; i++)
        {
            m_matrix[i] = matrix.m_matrix[i];
        }
    }

    //Конструктор перемещения
    Matrix(Matrix&& matrix) noexcept : Matrix()
    {
        if (matrix.m_matrix == nullptr)
        {
            throw std::runtime_error("Hui");
        }
        std::swap(m_matrix, matrix.m_matrix);
        m_range = matrix.m_range;
               
    }

    Matrix(std::initializer_list<T> list) : m_range(std::sqrt(list.size())), m_matrix(new T[list.size()])
    {
        if (std::sqrt(list.size()) - static_cast<int>(std::sqrt(list.size())) > 0.0001)
        {
            throw std::runtime_error("Nevozmozhno sozdat kvadratnuyu matritsu");
        }

        int i = 0;
        for(auto a: list)
        {
            m_matrix[i] = a;
            i++;
        }
    }

    

    ~Matrix()
    {               
            delete[] m_matrix;
    
    }

    

};


template<class T>
Matrix<T> operator*(int value, const Matrix<T>& matrix)
{
    return matrix * value;
}



int main()
{
    int countErr = 0;
    try
    {
        for (int i = 0; i < 1; i++)
        {
            Matrix<int> a{1, 2, 3, 4, 5, 6, 7, 8, 9};
            Matrix<int> b = a;
            Matrix<int> c = { 9, 8, 7, 6, 5, 4, 3, 2, 1 };
            Matrix<int> d{ c };
            if (a != b)
            {
                countErr++;
            }
            if (c != d)
            {
                countErr++;
            }
            if (a + b != Matrix<int>{2, 4, 6, 8, 10, 12, 14, 16, 18})
            {
                countErr++;
            }
            if (a * c != Matrix<int>{30, 24, 18, 84, 69, 54, 138, 114, 90})
            {
                countErr++;
            }
            if (d * 3 != Matrix<int>{27, 24, 21, 18, 15, 12, 9, 6, 3})
            {
                countErr++;
            }
            
        }
        std::cout << countErr;
        
    }
    catch(const std::exception& e)
    {
        std::cout << e.what();
    }
    float k = 2.0 - 1.0;
    int a = 0;
}


