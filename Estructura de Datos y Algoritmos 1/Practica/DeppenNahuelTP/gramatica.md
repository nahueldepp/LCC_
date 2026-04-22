boceto de gramatiga 
<Programa> ::= <Declaracion>
<Declaracion> ::= <Defl>|<Deff>|<Apply>|<Search>|<Exit> '\n'

<Defl>::= 'defl' <ID> '=' '['<ExprecionLista>']' ';'
<ExprecionLista>::= INT (',' INT )*

<Deff>::= 'deff' <ID> '=' <Instruccion>+ ';'
<Instruccion> ::= <ID> | <FuncionPrimitiva> | '<' <Instruccion>+ '>'
<FuncionPrimitiva>::= '0i'|'0d'|'Si'|'Sd'|'Di'|'Dd'

<Apply>::= 'apply' <ID> '[' <ExprecionLista> ']' ';'

<Search>::= 'search' '{' <ParDeListas>+ '}' ';'
<ParDeListas>::= <ID> ',' <ID> ';'

<ID> ::= CHAR (CHAR | INT)*

<Exit>::= 'exit' ';'