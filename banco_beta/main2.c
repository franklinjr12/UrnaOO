
#include "sqlite3.h"//inclue o header padrao do sqlite3

#define LOCAL_DB "sea.s3db"
// sqlite database pointer 
sqlite3 *ponteiroDB;

bool bancoAberto = false; //instancia o banco como 0 ou seja, fechado
bool conectaDB () //metodo conectar no banco
{
    if ( sqlite3_open(LOCAL_DB, &ponteiroDB) == SQLITE_OK )//passa o local que esta o banco e um ponteiro do banco
    {
        bancoAberto = true; //depois de aberto o banco retorna true
        return true;
    }         

    return false;
};

void DisconectaBanco ()
{
    if ( bancoAberto == true ) //verifica se o banco esta aberto, depois fecha
    {
        sqlite3_close(ponteiroDB);
    };
};

using namespace std;

int main(){
	return 0;
}