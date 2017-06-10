#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

#include "sqlite3.h"//inclue o header padrao do sqlite3
#define LOCAL_DB "banco.db3" //local padrao do banco de dados

// sqlite database pointer 
sqlite3 *ponteiroDB;

class BancoDados(){
public:
	bool conectaDB ();
	void DesconectaDB ();
}

bool bancoAberto = false; //instancia o banco como 0 ou seja, fechado
bool conectaDB () //metodo conectar no banco
{
    if ( sqlite3_open(LOCAL_DB, &ponteiroDB) == SQLITE_OK )//passa o local que esta o banco e um ponteiro do banco
    {
        bancoAberto = true; //depois de aberto o banco retorna true
        return true;
        cout << "Banco aberto" << endl;
    }         
    cout << "banco nao encontrado" << endl;
    return false;
};

void DesconectaDB ()
{
    if ( bancoAberto == true ) //verifica se o banco esta aberto, depois fecha
    {
        sqlite3_close(ponteiroDB);
    };
};

// Metodo de adicionar sessao ao banco de dados
int addSessaoDB(string id, string nome)
{
	/*
    // get the student data from user 
    student stud = getStudent();
    */

    std::stringstream strm;

    //passagem dos valores
    strm << "insert into sessoes(id_Sessao,nome_Sessao) values('" << id << "','" << nome << "')";

    string s = strm.str();
    char *str = &s[0];
    
    sqlite3_stmt *statement;

    int result;
    //char *query="insert into student(roll,name,cgpa)values(4,'uuu',6.6)";
    char *query = str;
    {
        if(sqlite3_prepare(ponteiroDB,query,-1,&statement,0)==SQLITE_OK)
        {
            int res=sqlite3_step(statement);
            result=res;
            sqlite3_finalize(statement);
        }
        return result;
    }
    return 0;
}

// listar dados da sessao
void listarSessao(string id)
{
     std::stringstream sessosListar;
     std::stringstream candidatosListar;

    //passagem dos valores, no caso so ira passar o id da sessao
    sessosListar << "select * from sessoes WHERE id_Sessao = '" << id << "' ";
    
    //candidatosListar << "select * from candidatos WHERE id_Sessao = '" << id << "' ";

    string s = sessosListar.str();

    char *str = &s[0];
    
    sqlite3_stmt *statement;
    char *query = str;


    if ( sqlite3_prepare(ponteiroDB, query, -1, &statement, 0 ) == SQLITE_OK ) 
    {
        int ctotal = sqlite3_column_count(statement);
        int res = 0;

        while ( 1 )         
        {
            res = sqlite3_step(statement);

            if ( res == SQLITE_ROW ) 
            {
                for ( int i = 0; i < ctotal; i++ ) 
                {
                    string s = (char*)sqlite3_column_text(statement, i);
                    // print or format the output as you want 
                    cout << s << " " ;
                }
                cout << endl;
            }
            
            if ( res == SQLITE_DONE || res==SQLITE_ERROR)    
            {
                cout << "done " << endl;
                break;
            }    
        }
    }
}

int main(){

	bancoAberto = conectaDB();

	if ( bancoAberto ) 
		cout << "Connected Successful" << endl;
	else cout << "connection failed " << endl;

	//chama funcao adicionar sessao ao banco de dados
	addSessaoDB("OI123","Teste frank gay, apartamento");
	listarSessao("OI123");
	//chama funcao de listar as sessoes criadas

	DesconectaDB();


	return 0;
}