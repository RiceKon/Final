#include "stokenize.h"

int STokenizer::_table[MAX_ROWS][MAX_COLUMNS];

STokenizer::STokenizer()
{
    make_table(_table);
    _pos = 0;
    _done = false;
    TypeArray();
}

STokenizer::STokenizer(char str[])
{
    make_table(_table);
    _pos = 0;
    _done = false;
    strcpy(_buffer, str);
    TypeArray();
}

bool STokenizer::done()
{ // true: there are no more tokens
    return _done;
}

bool STokenizer::more()
{ // true: there are more tokens
    return !_done;
}
//

//---------------
// extract one token (very similar to the way cin >> works)

// set a new string as the input string
void STokenizer::set_string(char str[])
{
    strcpy(_buffer, str);
}

Queue<Token *> STokenizer::tokenize()
{
    _tokens.clear();
    Token temp;

    *this >> temp;
    string str = "";
    while (more())
    {
        if (temp.getValue() != " ")
        {
            str = temp.getValue();
            _tokens.push(new Token(str));
        }
        str = "";
        *this >> temp;
    }
    return _tokens;
}

STokenizer &operator>>(STokenizer &s, Token &t)
{
    s._done = false;
    string temp;
    int state = 0;

    if (s._pos >= strlen(s._buffer))
    {
        s._done = true;
        s._pos = 0;
        return s;
    }
    s.get_token(state, temp);

    if (state != -1)
    {
        state = s._success_table[state];
    }
    t = Token(temp);
    return s;
}

void STokenizer::TypeArray()
{
    // alpha
    _success_table[1] = TOKEN_ALPHA;
    _success_table[3] = TOKEN_ALPHA;
    // number
    _success_table[5] = TOKEN_NUMBER;
    _success_table[7] = TOKEN_NUMBER;
    // space
    _success_table[10] = TOKEN_SPACE;

    _success_table[12] = TOKEN_PUNC;
}

// create table for all the tokens we will recognize
//                       (e.g. doubles, words, etc.)
void STokenizer::make_table(int _table[][MAX_COLUMNS])
{

    init_table(_table);
    // alpha

    mark_success(_table, 1); // words
    mark_fail(_table, 2);    // words with (') they're
    mark_success(_table, 3); // continue with re

    mark_cells(0, _table, ALFA, 1);
    mark_cells(1, _table, ALFA, 1);
    mark_cell(1, _table, '\'', 2);
    mark_cells(2, _table, ALFA, 3);
    mark_cells(3, _table, ALFA, 3);
    // 0 - 3

    // digit
    mark_success(_table, 5);
    mark_fail(_table, 6);
    mark_success(_table, 7);

    mark_cells(0, _table, DIGITS, 5);
    mark_cells(5, _table, DIGITS, 5);
    mark_cell(5, _table, '.', 6);
    mark_cells(6, _table, DIGITS, 7);
    mark_cells(7, _table, DIGITS, 7);
    // 5 - 7

    // space

    mark_success(_table, 10);

    mark_cells(0, _table, SPACES, 10);
    mark_cells(10, _table, SPACES, 10);

    // 10 - 10

    // punct

    mark_success(_table, 12);

    mark_cells(0, _table, PUNC, 12);
    mark_cells(12, _table, PUNC, 12);
}

// extract the longest string that match
//      one of the acceptable token types

// cases, UNKNOWN, END,

bool STokenizer::get_token(int &start_state, string &token)
{
    int success, state = 0, potential_size = 0, size = 0;

    string temp(_buffer);
    for (int i = _pos; i < temp.length() + 1; i++)
    {
        // get the asccii value
        int check = static_cast<int>(_buffer[i]);
        // check the state (136 to 145)
        //  get the state
        state = check > 0 ? _table[state][check] : -1;

        // check if its a valid string or pos the string is at the end
        if (state == -1)
        {
            // add the string
            if (size == 0)
            {
                start_state = state;
                size++;
            }
            token = temp.substr(_pos, size);
            // update the postition
            _pos += size;
            return true;
            // if the ascii vaule unknown the state is -1
        }
        // if not a success state update the potential size
        if (_table[state][0] == 1)
        {
            start_state = state;
            potential_size++;
            size = potential_size;
            // if success state update my state and potential size
        }
        else if (_table[state][0] == 0)
        {
            potential_size++;
        }
    }
    return false;
}
