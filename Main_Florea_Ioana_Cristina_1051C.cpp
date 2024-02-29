#include <iostream>
#include <string>
#include <math.h>
#include <fstream>
#include <sstream>
#include<vector>


/// CToken.h
class CToken {
private:
	double m_value;
	char m_operator;
	static const char* m_stc_caractere_operatori;

public:
	CToken();
	CToken(double a_val, char a_operator = '\0');
	CToken(const CToken& tk);
	~CToken();

	CToken& operator=(const CToken& tk);

	double getValue() const;
	void setValue(double a_value);

	char getOperator() const;
	void setOperator(char a_operator);

	static std::string getStc_caractere_operatori();

	friend std::ostream& operator<<(std::ostream& out, const CToken tk);
	friend std::istream& operator>>(std::istream& in, CToken& tk);
	bool operator == (const CToken& right);

	explicit operator double() const;

private:
	static bool e_operator_valid(char a_operator);
};

////CToken.cpp

std::ostream& operator<<(std::ostream& out, const CToken tk)
{
    out << "[Token: ";
    if (tk.m_operator == '\0')
    {
        out << true << ";" << tk.m_value;
    }
    else
    {
        out << false << ";" << tk.m_operator;
    }
    out << "]";
    return out;
}

std::istream& operator>>(std::istream& in, CToken& tk)
{
    in.ignore(strlen("[Token: "));

    bool isValue;
    
    in >> isValue;
    if (in.fail())
    {
        std::cerr << "Valoarea introdusa trebuie sa fie 0 sau 1 " << std::endl;
    }
    else
    {
        in.ignore(1); 
        if (isValue == true)
        {
            double val;
            tk.setOperator('\0');
            
            in >> val;
            tk.setValue(val);
            
        }
        else
        {
            char op;
            tk.setValue(0);
          

            in >> op;
            tk.setOperator(op);
            
        }
        in.ignore(1); 
    }
    return in;
}


CToken::CToken() :
    m_value(0),
    m_operator('\0')
{
    setValue(0);
    setOperator('\0');
}

CToken::CToken(double a_val, char a_operator) :
    m_value(0),
    m_operator('\0')
{
    setValue(a_val);
    setOperator(a_operator);
}

CToken::CToken(const CToken& tk) :
    m_value(0),
    m_operator('\0')
{
    
    setValue(tk.getValue());
    setOperator(tk.getOperator());
}

CToken::~CToken()
{
    setValue(0);
    setOperator('\0');
}

CToken& CToken::operator= (const CToken& tk)
{
    setValue(tk.getValue());
    setOperator(tk.getOperator());
    return *this;
}

bool CToken::operator== (const CToken& right)
{
    return (m_value == right.m_value && m_operator == right.m_operator);
}

CToken::operator double() const
{
    return m_value;
}

double CToken::getValue() const   
{
    return m_value;
}

void CToken::setValue(double a_value)
{
    m_value = a_value;
}

char CToken::getOperator() const
{
    return m_operator;
}

void CToken::setOperator(char a_operator)
{
    if (e_operator_valid(a_operator))
        m_operator = a_operator;
}

const char* CToken::m_stc_caractere_operatori = "()[]+-*/^#";

std::string CToken::getStc_caractere_operatori()
{
    return m_stc_caractere_operatori;
}

bool CToken::e_operator_valid(char a_operator)
{

    if (a_operator == '\0')
        return true;

    const char* ptr = strchr(m_stc_caractere_operatori, a_operator);
    return (ptr != nullptr);
}

////CoadaTempl.h

template<typename TData>
class Coada
{
private:
    TData* array;
    static TData stc_dummy_element;
    size_t varf;
    size_t coada;
    size_t size_array;
    const int MAX_SIZE = 5;

public:
    Coada()
    {
        array = nullptr;
        varf = 0;
        coada = 0;
        size_array = 0;
    }

    ~Coada()
    {
        clean();
    }

    Coada(const Coada& rCoada) :
        array(nullptr),
        varf(0),
        coada(0),
        size_array(0)

    {
        if (rCoada.array != nullptr)
        {
            array = new TData[rCoada.size_array];
            for (size_t i = 0; i < rCoada.size_array; i++)
                array[i] = rCoada.array[i];
        }
        varf = rCoada.varf;
        coada = rCoada.coada;
        size_array = rCoada.size_array;

    }

    size_t getVarf()
    {
        return varf;
    }

    void setVarf(int c_varf)
    {
        if (c_varf >= 0 && c_varf < size_array)
            varf = c_varf;
    }

    size_t getCoada()
    {
        return coada;
    }

    void setCoada(int c_coada)
    {
        if (c_coada >= 0 && c_coada < size_array)
            coada = c_coada;
    }

    size_t getSize_array()
    {
        return size_array;
    }

    void setArray(TData c_array, int c_size_array)
    {
        if (c_array != NULL && c_size_array > 0)
        {
            if (size_array != NULL) {
                delete[] size_array;
            }
            array = new int[c_size_array];
            size_array = c_size_array;
            for (int i = 0; i < size_array; i++)
                array[i] = c_array[i];

        }
    }

    TData* getArray()
    {
        if (size_array > 0 && array != nullptr)
        {
            TData* copie = new int[size_array];
            for (int i = 0; i < size_array; i++)
            {
                copie[i] = array[i];
            }
            return copie;
        }
        else
        {
            return nullptr;
        }

    }

    const int getMAX_SIZE()
    {
        return MAX_SIZE;
    }

    TData getStc_dummy_element()
    {
        return stc_dummy_element;
    }

    Coada operator=(const Coada& rCoada)
    {
        clean();
        if (rCoada.array != nullptr)
        {
            array = new TData[rCoada.size_array];
            for (size_t i = 0; i < rCoada.size_array; i++)
                array[i] = rCoada.array[i];
        }
        varf = rCoada.varf;
        coada = rCoada.coada;
        size_array = rCoada.size_array;

    }

    bool put(TData val) //enqueue
    {
        if (array == nullptr)
        {
            size_array = MAX_SIZE;
            array = new TData[size_array];
            if (!array)
                return false; // memorie insuficienta

        }
        else
        {
            if (coada >= size_array)
            {
                size_t new_size = size_array * 2;
                TData* array_nou = new TData[new_size];
                if (!array_nou)
                    return false; // memorie insuficienta

                for (size_t i = 0; i < size_array; i++)
                {
                    array_nou[i] = array[i];
                }
                delete[] array;
                array = array_nou;
                size_array = new_size;
            }
        }
        array[coada] = val;
        coada++;
        return true;
    }

    bool get(TData& val) //dequeue
    {
        bool ret = false;
        if (!is_empty())
        {
            val = array[varf];
            varf++;
            if (is_empty())
            {
                varf = coada = 0;
            }
            ret = true;
        }
        return ret;
    }

    bool is_empty() const
    {
        return (coada == varf);
    }

    //returneaza true daca nu este goala coada
    bool operator! () const
    {
        return (is_empty() == false);
    }

    TData& operator[](int index)
    {
        if (varf < coada && array != nullptr)
        {
            if (index >= varf && index <= coada)
                return array[index];
        }
        return stc_dummy_element;
    }

    void clean()
    {
        if (array != nullptr)
        {
            delete[] array;
        }
        array = nullptr;
        varf = 0;
        coada = 0;
        size_array = 0;
    }
    friend std::ostream& operator<<(std::ostream& out, const Coada& queue)
    {
        out << "[Coada: ";
        out << queue.varf;
        out << " ";
        out << queue.coada;
        if (queue.array != nullptr) {
            for (size_t i_elem = queue.varf; i_elem < queue.coada; i_elem++) {
                out << queue.array[i_elem];
            }
        }
        out << "]" << std::endl;
        return out;
    }

    friend std::istream& operator>>(std::istream& in, Coada& queue)
    {
        queue.clean();
        in.ignore(strlen("[Coada: "));
        size_t nQueueVarf;
        size_t nQueueCoada;
        in >> nQueueVarf;

        in >> nQueueCoada;
        TData val;
        for (size_t i = nQueueVarf; i < nQueueCoada; i++)
        {
            in >> val;
            queue.put(val);
        }
        in.ignore(1);
        return in;
    }
};

template <typename TData>
TData Coada<TData>::stc_dummy_element = TData();

////StivaTempl.h

template<typename TData>
class Stiva
{
private:
    TData* array;
    static TData stc_dummy_element;
    int varf;
    int size_array;
    const int  MAX_SIZE;

public:
    Stiva() :MAX_SIZE(5)
    {
        array = nullptr;
        varf = -1;
        size_array = 0;
    }

    ~Stiva()
    {
        clean();
    }

    Stiva(const Stiva& rStiva) :MAX_SIZE(5),
        array(nullptr),
        varf(-1),
        size_array(0)

    {
        if (rStiva.array != nullptr)
        {
            array = new TData[rStiva.size_array];
            for (size_t i = 0; i < rStiva.size_array; i++)
                array[i] = rStiva.array[i];
        }
        varf = rStiva.varf;

        size_array = rStiva.size_array;

    }

    int getVarf() const
    {
        return varf;
    }
    void setVarf(int s_varf)
    {
        if (s_varf >= -1 && s_varf < size_array)
            varf = s_varf;
    }
    int getSize_array() const
    {
        return size_array;
    }

    int getMAX_SIZE() const
    {
        return MAX_SIZE;
    }

    void setArray(TData s_array, int s_size_array)
    {
        if (s_array != NULL && s_size_array > 0)
        {
            if (size_array != NULL) {
                delete[] size_array;
            }
            array = new int[s_size_array];
            size_array = s_size_array;
            for (int i = 0; i < size_array; i++)
                array[i] = s_array[i];
        }
    }

    TData* getArray()
    {
        if (size_array > 0 && array != nullptr)
        {
            TData* copie = new int[size_array];
            for (int i = 0; i < size_array; i++)
            {
                copie[i] = array[i];
            }
            return copie;
        }
        else
        {
            return nullptr;
        }

    }

    TData getStc_dummy_element()
    {
        return stc_dummy_element;
    }

    Stiva operator=(const Stiva& rStiva)
    {
        clean();
        if (rStiva.array != nullptr)
        {
            array = new TData[rStiva.size_array];
            for (size_t i = 0; i < rStiva.size_array; i++)
                array[i] = rStiva.array[i];
        }
        varf = rStiva.varf;
        size_array = rStiva.size_array;

    }

    //prefix++
    void operator++ ()
    {
        push(stc_dummy_element);
    }

    //postfix++
    void operator++ (int i)
    {
        push(stc_dummy_element);
    }

    //prefix--
    void operator-- ()
    {
        if (!is_empty())
        {
            TData d = pop();
        }
    }

    //postfix--
    void operator-- (int i)
    {
        if (!is_empty())
        {
            TData d = pop();
        }
    }

    bool push(TData val)
    {
        if (array == nullptr)
        {
            size_array = MAX_SIZE;
            array = new TData[size_array];
            if (!array)
                return false; // memorie insuficienta

        }
        else
        {
            if (varf >= size_array - 1)
            {
                TData* array_nou = new TData[size_array * 2];
                if (!array_nou)
                    return false; // memorie insuficienta

                for (int i = 0; i < size_array; i++)
                {
                    array_nou[i] = array[i];
                }
                size_array *= 2;
                delete[] array;
                array = array_nou;
            }
        }
        varf++;
        array[varf] = val;

        return true;
    }

    TData pop()
    {
        TData t(0);
        if (!is_empty()) {
            t = array[varf];
            varf--;
        }
        return t;
    }

    TData top()
    {
        if (varf >= 0 && varf < size_array && array != nullptr)
            return array[varf];
        else
            return TData();
    }

    bool is_empty()
    {
        return (varf == -1);
    }

    void clean()
    {
        if (array != nullptr)
        {
            delete[] array;
        }
        array = nullptr;
        varf = -1;
        size_array = 0;
    }

    friend std::ostream& operator<<(std::ostream& out, const Stiva& stiva)
    {
        out << "[Stiva: ";
        out << stiva.varf;
        if (stiva.array != nullptr) {
            for (int i_elem = 0; i_elem <= stiva.varf; i_elem++) {
                out << stiva.array[i_elem];
            }
        }
        out << "]" << std::endl;
        return out;
    }

    friend std::istream& operator>>(std::istream& in, Stiva& stiva)
    {

        stiva.clean();

        in.ignore(strlen("[Stiva: "));
        int nStivaVarf;
        in >> nStivaVarf;

        TData val;
        for (int i = 0; i <= nStivaVarf; i++)
        {
            in >> val;
            stiva.push(val);
        }
        in.ignore(1);
        return in;
    }
};

template <typename TData>
TData Stiva<TData>::stc_dummy_element = TData();

////Calculator.h

class Calculator
{
public:
    static bool este_cifra(char c);

    static int prioritate(char c);

    static void sterge_spatii(char* str);

    bool forma_poloneza_inversa(Coada<CToken> input, Coada<CToken>& queue);

    double evaluare_fpi(Coada<CToken>& queue);

    bool verifica_expresie(const char* expresie);

    bool rezultat_expresie(std::string sExpresie, double& rez);

    void rezultate_expresii_din_fisier(std::string nume_fisier);

    virtual std::string showMainMenu();
    virtual std::string showSubMenu();

};

////Calculator.cpp

bool Calculator::este_cifra(char c)
{
    return (c >= '0' && c <= '9');
}

int Calculator::prioritate(char c)
{
    switch (c) {
    case '+':
    case '-':
        return 2;
    case '*':
    case '/':
        return 3;
    case '^':
    case '#':
        return 4;
    default:
        return 1;
    }
}

void Calculator::sterge_spatii(char* str)
{
    int i = 0, j = 0;
    while (str[i])
    {
        if (str[i] != ' ')
            str[j++] = str[i];
        i++;
    }
    str[j] = '\0';

}

bool Calculator::forma_poloneza_inversa(Coada<CToken> input, Coada<CToken>& queue)
{
    Stiva<char> stack_FPI;
    CToken t;
    char f;
    CToken ff;
    while (!input)
    {
        bool get_succeeded = input.get(t);
        if (!get_succeeded)
        {
            std::cout << "Invalid get";
            return 0;
        }
        if (t.getOperator() == '\0')
        {
            bool ret = queue.put(t);
            if (!ret)
            {
                std::cout << "Invalid put";
                return 0;
            }
        }
        if (t.getOperator() == '(' || t.getOperator() == '[')
        {
            stack_FPI.push(t.getOperator());
        }
        if (t.getOperator() == ')')
        {
            if (stack_FPI.is_empty())
            {
                std::cout << "Stack gol1";
                return 0;
            }
            f = stack_FPI.pop();
            while (f != '(')
            {
                bool ret;
                ff = CToken(0, f);
                ret = queue.put(ff);
                if (!ret)
                {
                    std::cout << "Invalid put";
                    return 0;
                }
                if (stack_FPI.is_empty())
                {
                    std::cout << "Stack gol2";
                    return 0;
                }

                f = stack_FPI.pop();


            }
        }
        if (t.getOperator() == ']')
        {
            if (stack_FPI.is_empty())
            {
                std::cout << "Stack gol3";
                return 0;
            }
            f = stack_FPI.pop();
            while (f != '[')
            {
                bool ret;
                ff = CToken(0, f);
                ret = queue.put(ff);
                if (!ret)
                {
                    std::cout << "Invalid put";
                    return 0;
                }
                if (stack_FPI.is_empty())
                {
                    std::cout << "Stack gol4";
                    return 0;
                }

                f = stack_FPI.pop();
            }
        }
        if (t.getOperator() == '^' || t.getOperator() == '#' || t.getOperator() == '-' || t.getOperator() == '+' || t.getOperator() == '*' || t.getOperator() == '/')
        {
            if (stack_FPI.is_empty() == 0)
            {
                while (!stack_FPI.is_empty() && prioritate(stack_FPI.top()) > prioritate(t.getOperator()))
                {
                    if (stack_FPI.is_empty())
                    {
                        std::cout << "Stack gol5";
                        return 0;
                    }
                    f = stack_FPI.pop();
                    ff = CToken(0, f);
                    bool ret = queue.put(ff);
                    if (!ret)
                    {
                        std::cout << "Invalid put";
                        return 0;
                    }
                }
            }

            stack_FPI.push(t.getOperator());
        }
    }
    while (!stack_FPI.is_empty())
    {
        f = stack_FPI.pop();
        ff = CToken(0, f);
        bool ret = queue.put(ff);
    }
    return 1;
}

double Calculator::evaluare_fpi(Coada<CToken>& queue)
{
    Stiva<double> stack_evaluare;
    CToken t;
    if (!(queue.is_empty()))
    {
        do
        {

            bool get_succeeded = queue.get(t);
            if (t.getOperator() == '\0')
            {
                stack_evaluare.push(t.getValue());
            }
            else {
                double v1, v2, rez = 0;
                if (stack_evaluare.is_empty() == 0)
                {
                    v1 = stack_evaluare.pop();
                }
                else
                {
                    std::cout << std::endl << "Calcul nedefinit" << std::endl;
                    return 0;
                }
                if (stack_evaluare.is_empty() == 0)
                {
                    v2 = stack_evaluare.pop();
                }
                else
                {
                    std::cout << std::endl << "Calcul nedefinit" << std::endl;
                    return 0;
                }


                switch (t.getOperator())
                {
                case '+':
                    rez = v1 + v2;
                    break;
                case '-':
                    rez = v2 - v1;
                    break;
                case '*':
                    rez = v1 * v2;
                    break;
                case '/':
                    if (v1 == 0)
                    {
                        std::cout << std::endl << "Calcul nedefinit" << std::endl;
                        return 0;
                    }
                    else
                    {
                        rez = v2 / v1;
                        break;
                    }
                case '^':
                    rez = pow(v2, v1);
                    break;
                case '#':
                    if (v1 == 0)
                    {
                        std::cout << std::endl << "Calcul nedefinit" << std::endl;
                        return 0;
                    }
                    else
                    {
                        rez = pow(v2, 1 / v1);
                        break;
                    }
                }
                stack_evaluare.push(rez);
            }

        } while (!(queue.is_empty()));
    }
    return stack_evaluare.pop();
}

bool Calculator::verifica_expresie(const char* expresie)
{
    int count_paranteze_rotunde = 0;
    int count_paranteze_patrate = 0;
    int count_punct;
    for (size_t i = 0; i < strlen(expresie); i++) {

        if ((expresie[i] != '(') &&
            (expresie[i] != '[') &&
            (expresie[i] != ')') &&
            (expresie[i] != ']') &&
            (expresie[i] != '.') &&
            (expresie[i] != '^') &&
            (expresie[i] != '#') &&
            (expresie[i] != '-') &&
            (expresie[i] != '+') &&
            (expresie[i] != '*') &&
            (expresie[i] != '/') &&
            (expresie[i] != 'x') &&
            !este_cifra(expresie[i]))
        {
            std::cout << "Expresie invalida (eroarea 1)" << std::endl;
            return 0;
        }
    }

    for (size_t i = 0; i < strlen(expresie); i++)
    {
        if (este_cifra(expresie[i]) == 1 || expresie[i] == '.')
        {
            count_punct = 0;
            if (expresie[i] == '.')
                count_punct++;
            while (i + 1 < strlen(expresie) && (este_cifra(expresie[i + 1]) == 1 || expresie[i + 1] == '.') && count_punct != 2)
            {
                i++;
                if (expresie[i] == '.')
                    count_punct++;

            }
            if (count_punct == 2)
            {
                count_punct = 0;
                std::cout << "Expresie invalida (eroarea 2)" << std::endl;
                return 0;
            }
        }
        else
        {

            switch (expresie[i])
            {
            case '(':
                if (count_paranteze_rotunde == 1)
                {
                    std::cout << "Expresie invalida (eroarea 3)" << std::endl;
                    return 0;
                }
                count_paranteze_rotunde++;
                break;
            case ')':
            {
                count_paranteze_rotunde--;
                if ((count_paranteze_rotunde) < 0)
                {
                    std::cout << "Expresie invalida (eroarea 4)" << std::endl;
                    return 0;
                }

                break;
            }
            case '[':
            {  if (count_paranteze_rotunde > 0 || count_paranteze_patrate == 1)
            {
                std::cout << "Expresie invalida (eroarea 5)" << std::endl;
                return 0;
            }
            else
            {
                count_paranteze_patrate++;
                break;
            }
            }
            case ']':
            {  if (count_paranteze_rotunde > 0)
            {
                std::cout << "Expresie invalida (eroarea 6)" << std::endl;
                return 0;
            }
            else
            {
                count_paranteze_patrate--;
                if ((count_paranteze_patrate) < 0)
                {
                    std::cout << "Expresie invalida (eroarea 7)" << std::endl;
                    return 0;
                }
            }
            break;

            }
            case 'x':
                if ((i == 0 || expresie[i - 1] == '(' || expresie[i - 1] == '[' || expresie[i - 1] == '-' || expresie[i - 1] == '+' || expresie[i - 1] == '/' || expresie[i - 1] == '#' || expresie[i - 1] == '*' || expresie[i - 1] == '^') && (expresie[i + 1] == ')' || expresie[i + 1] == ']' || expresie[i + 1] == '-' || expresie[i + 1] == '+' || expresie[i - 1] == '/' || expresie[i + 1] == '#' || expresie[i + 1] == '*' || expresie[i + 1] == '^' || expresie[i + 1] == '\0'))
                {
                    break;
                }
                else
                {
                    std::cout << "Expresie invalida (eroarea 8)" << std::endl;
                    return 0;
                }
            case '-':
            case '+':
            {
                if ((i == 0 || expresie[i - 1] == '(' || expresie[i - 1] == '[') && (este_cifra(expresie[i + 1]) == 1 || expresie[i + 1] == '.' || expresie[i + 1] == 'x'))
                {
                }
                else
                {
                    bool b1 = (este_cifra(expresie[i - 1]) == 1 || expresie[i - 1] == '.' || expresie[i - 1] == 'x' || expresie[i - 1] == ')' || expresie[i - 1] == ']');
                    bool b2 = (este_cifra(expresie[i + 1]) == 1 || expresie[i + 1] == '.' || expresie[i + 1] == 'x' || expresie[i + 1] == '(' || expresie[i + 1] == '[');
                    if (b1 && b2)

                    {
                    }
                    else
                    {
                        std::cout << "Expresie invalida (eroarea 9)" << std::endl;
                        return 0;
                    }
                }
                break;
            }
            case '*':
            case '/':
            case '^':
            case '#':
            {   if ((este_cifra(expresie[i - 1]) == 1 || expresie[i - 1] == '.' || expresie[i - 1] == 'x' || expresie[i - 1] == ')' || expresie[i - 1] == ']') && (este_cifra(expresie[i + 1]) == 1 || expresie[i + 1] == '.' || expresie[i + 1] == 'x' || expresie[i + 1] == '(' || expresie[i + 1] == '['))
            {
            }
            else
            {
                std::cout << "Expresie invalida (eroarea 10)" << std::endl;
                return 0;
            }
            break;
            }
            }
        }
    }
    if (count_paranteze_patrate != 0)
    {
        std::cout << "Expresie invalida (eroarea 11)" << std::endl;
        return 0;
    }
    if (count_paranteze_rotunde != 0)
    {
        std::cout << "Expresie invalida (eroarea 12)" << std::endl;
        return 0;
    }

    return 1;
}

bool Calculator::rezultat_expresie(std::string sExpresie, double& rez)
{
    bool is_ok_eval = false;
    rez = 0;

    char* c = nullptr;
    Coada<CToken> input;

    Coada<CToken> queue;

    c = new char[strlen(sExpresie.c_str()) + 1];
    strcpy_s(c, strlen(sExpresie.c_str()) + 1, sExpresie.c_str());
    sterge_spatii(c);
    bool verify = verifica_expresie(c);
    if (verify)
    {
        for (size_t i = 0; i < strlen(c); i++)
        {
            char c_i = c[i];
            if (c_i == 'x')
            {
                std::ifstream fin;
                fin.open("ult_rez.bin", std::ios::in | std::ios::binary);
                if (fin.is_open())
                {
                    double d;
                    fin >> d;
                    if (fin.fail())
                    {
                        std::cout << "Nu s-a putut citi nici un rezultat din fisierul binar pentru a fi inlocuit in variabila x.\n";

                    }
                    else
                    {
                        CToken tkvar(d);
                        bool ret = input.put(tkvar);
                    }
                    fin.close();
                }
                else
                    std::cout << "Nu s-a putut citi valoarea lui x din fisierul binar.\n";

            }
            else if (este_cifra(c_i) == 1 || c_i == '.')
            {
                std::string numar;
                numar.push_back(c_i);

                while (i + 1 < sExpresie.length() && (este_cifra(c[i + 1]) == 1 || c[i + 1] == '.'))
                {
                    numar.push_back(c[i + 1]);
                    i++;
                }
                CToken num(stod(numar));
                bool ret = input.put(num);
            }
            else
            {
                if ((c_i == '+' || c_i == '-') && (i == 0 || c[i - 1] == '(' || c[i - 1] == '['))
                {
                    std::string numar;
                    numar.push_back(c_i);

                    while (i + 1 < strlen(c) && (este_cifra(c[i + 1]) == 1 || c[i + 1] == '.'))
                    {
                        numar.push_back(c[i + 1]);
                        i++;
                    }
                    CToken num(stod(numar));
                    bool ret = input.put(num);
                }
                else
                {
                    CToken oper(0, c_i);
                    bool ret = input.put(oper);
                }
            }

        }

        bool fpi = forma_poloneza_inversa(input, queue);
        if (!fpi) {
            is_ok_eval = false;
        }
        else {
            rez = evaluare_fpi(queue);
            is_ok_eval = true;
        }
    }
    else {
        is_ok_eval = false;
    }

    if (c != nullptr) {
        delete[] c;
    }

    return is_ok_eval;
}

void Calculator::rezultate_expresii_din_fisier(std::string nume_fisier)
{
    std::ifstream fExpresii;
    fExpresii.open(nume_fisier, std::ios::in);
    if (fExpresii.is_open())
    {
        std::string sExpresie;
        while (std::getline(fExpresii, sExpresie)) {

            if (sExpresie.empty())
                continue;

            std::cout << "Expresia: " << sExpresie << std::endl;
            double rez = 0;
            if (!rezultat_expresie(sExpresie, rez))
            {
                std::cout << "Evaluare nereusita a expresiei." << std::endl;
            }
            else
                std::cout << "Rezultat: " << rez << std::endl;
            std::cout << "---------------------------" << std::endl;
        }
        fExpresii.close();
    }
    else
        std::cout << "Fisierul " << nume_fisier << " nu a fost deschis.";
}
std::string Calculator::showMainMenu()
{
    std::cout << "\nMeniu principal:: Introduceti:" << std::endl;;
    return "exit";
}

std::string Calculator::showSubMenu()
{
    std::cout << "\n\tSubmeniu:: Introduceti:" << std::endl;
    return "exit";
}

////AbstractConsoleMenu.h


class AbstractConsoleMenu
{
public:
    virtual void procesare_meniuri() = 0;
    static AbstractConsoleMenu* get_default_consola_calculator();
};

////ConsoleMenu.h

class ConsoleMenu : public Calculator, public AbstractConsoleMenu
{
private:
    std::vector<std::string> m_optiuni_main;
    std::vector<std::string> m_optiuni_sub;

    double m_ultimul_rezultat;
    bool   m_ultimul_rezultat_cu_succes;

    std::string showMainMenu();
    std::string showSubMenu();

    void sterge_ultim_rezultat_din_fisier();

    static std::string trim_la_stanga(const std::string& s);
    static std::string trim_la_dreapta(const std::string& s);
    static std::string trim(const std::string& s);

public:
    ConsoleMenu();

    void procesare_meniuri(); // functie virtuala mostenita din AbstractCM;
};


////ConsoleMenu.cpp

const std::string WHITESPACE = " \n\r\t\f\v";

std::string ConsoleMenu::trim_la_stanga(const std::string& s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}

std::string ConsoleMenu::trim_la_dreapta(const std::string& s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

std::string ConsoleMenu::trim(const std::string& s) {
    return trim_la_dreapta(trim_la_stanga(s));
}

ConsoleMenu::ConsoleMenu()
{
    m_ultimul_rezultat = 0;
    m_ultimul_rezultat_cu_succes = false;

    {
        m_optiuni_main.push_back("\t 1 pentru a citi ecuatiile dintr-un fisier.");
        m_optiuni_main.push_back("\t 2 pentru a citi ecuatiile de la tastatura.");
        m_optiuni_main.push_back("\t exit pentru a iesi din program.");
    }

    {
        m_optiuni_sub.push_back("\t\t 1 pentru a citi ecuatia.");
        m_optiuni_sub.push_back("\t\t 2 pentru a salva rezultatul curent.");
        m_optiuni_sub.push_back("\t\t exit pentru a iesi din submeniu.");
    }
}

std::string ConsoleMenu::showMainMenu()
{
    Calculator::showMainMenu();
    std::string input;
    for (auto it = m_optiuni_main.begin(); it != m_optiuni_main.end(); it++)
    {
        std::cout << *it << std::endl;
    }

    std::getline(std::cin, input);
    input = trim(input);
    return input;
}

std::string ConsoleMenu::showSubMenu()
{
    Calculator::showSubMenu();

    for (auto it = m_optiuni_sub.begin(); it != m_optiuni_sub.end(); it++)
    {
        std::cout << *it << std::endl;
    }

    std::string sInput;
    std::getline(std::cin, sInput);
    sInput = trim(sInput);

    return sInput;
}

void ConsoleMenu::sterge_ultim_rezultat_din_fisier()
{
    std::ofstream fout("ult_rez.bin", std::ios::out | std::ios::trunc | std::ios::binary);
    fout.close();
}

void ConsoleMenu::procesare_meniuri()
{
    sterge_ultim_rezultat_din_fisier();
    m_ultimul_rezultat = 0;
    m_ultimul_rezultat_cu_succes = false;

    std::string selectatMainMenu;
    bool isExitMainMenu = false;
    do
    {
        selectatMainMenu = showMainMenu();
        if (selectatMainMenu == "exit") {
            isExitMainMenu = true;
        }
        else if (selectatMainMenu == "1") {
            std::string nume_fisier;
            std::cout << "\tIntrodu numele fisierului.\n";
            std::getline(std::cin, nume_fisier);
            rezultate_expresii_din_fisier(nume_fisier);


        }
        else if (selectatMainMenu == "2") {
            m_ultimul_rezultat_cu_succes = false;

            sterge_ultim_rezultat_din_fisier();

            std::string selectatSubMenu;
            bool isExitSubMenu = false;
            do
            {
                selectatSubMenu = showSubMenu();
                if (selectatSubMenu == "exit") {
                    isExitSubMenu = true;
                }
                else if (selectatSubMenu == "1")
                {
                    std::cout << "\tIntrodu expresie:\n";
                    std::string sExpresie;
                    std::getline(std::cin, sExpresie);
                    double rez;
                    bool rez_cu_succes = rezultat_expresie(sExpresie, rez);
                    m_ultimul_rezultat = rez;
                    m_ultimul_rezultat_cu_succes = rez_cu_succes;
                    if (!m_ultimul_rezultat_cu_succes)
                    {
                        std::cout << "\tEvaluare nereusita a expresiei." << std::endl;
                    }
                    else
                    {
                        std::cout << "\tRezultat: " << rez << std::endl;
                    }

                }
                else if (selectatSubMenu == "2")
                {
                    if (m_ultimul_rezultat_cu_succes)
                    {
                        std::ofstream fout("ult_rez.bin", std::ios::out | std::ios::binary);
                        fout << m_ultimul_rezultat;
                        fout.close();
                        std::cout << "\tRezultatul a fost salvat in fisierul binar ult_rez.bin\n";
                    }
                    else
                        std::cout << "\tRezultatul nu s-a putut salva.\n";

                }
                else
                {
                    std::cout << "\tOptiune invalida. Introduceti alta optiune.\n";
                }

            } while (!isExitSubMenu);
        }
        else {
            std::cout << "Optiune invalida. Introduceti alta optiune.\n";
        }
    } while (!isExitMainMenu);
}


////AbstractConsoleMenu.cpp
AbstractConsoleMenu* AbstractConsoleMenu::get_default_consola_calculator()
{
    static ConsoleMenu stConsoleMenu;
    return &stConsoleMenu;
}

int main(int argc, char* argv[])
{
    if (argc == 2) {
        std::string strExpresie = argv[1];
        std::cout << "Expresia din linia de comanda este: " << strExpresie << std::endl;
        Calculator calc;
        double rez = 0;
        if (!calc.rezultat_expresie(strExpresie, rez))
        {
            std::cout << "Evaluare nereusita a expresiei." << std::endl;
        }
        else {
            std::cout << "Rezultat: " << rez << std::endl;
        }
        std::cout << "Exit" << std::endl;
    }
    else {
        AbstractConsoleMenu* ptrACM = AbstractConsoleMenu::get_default_consola_calculator();
        ptrACM->procesare_meniuri();
    }
    return 0;
}