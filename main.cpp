#include "condominium.h"
#include "property.h"

int main(){
	Condominium teste("And");
	Apartment mansaomelaca("rua do melo");
	teste.addProperty(mansaomelaca);

    return 0;
}