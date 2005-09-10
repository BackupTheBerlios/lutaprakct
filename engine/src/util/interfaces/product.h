#ifndef _PRODUCT_H_
#define _PRODUCT_H_

/** classe raiz da arquitetura da engine. é usada pela factory para encapsular o retorno
 * dela, assim elas podem se tornar abstratas o bastante para qualquer tipo
 * de subclasse que o cliente quiser criar usando uma factory.
 * So faz sentido usar essa classe se a subclasse for retornada como produto de alguma factory.
 * esse é o tipo de retorno de todas as factories devido a interface abstract factory
 */
 
 class product{
 
 public:
 	product(){};
 	~product(){};
 };

#endif //_PRODUCT_H_
