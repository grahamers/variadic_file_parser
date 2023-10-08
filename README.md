# variadic_file_parser
use of variadic templates along with deduction to parse csv like files. The separator can be other than ','

Its common for test case runs (and other scenarios) to have "CSV like" file that needs to be parsed and appropriate
fields populated into data structures/types.

For  example a line in a CSV file might be defined thus;

N,1, IBM,10,100, B,1

N denotes a "New Order", there follows a string (1), a string symbol "IBM" followed by 2 ints 
, a char denoting "B"uy or "S"ell side and an integer.

Similarly;

C,2,101,,,,

C denotes "C"ancel an order, the integers 2 and 101 denote client ID and Order ID, say.

And;

Q,2, 23, 99.99, true, 12.1223421234234

Q (replace say), followed by 2 integers, a double , a bool and then another double.

Instead of writing tedious string find/manilulation code, this approach can be used to parse lines. All that is needed 
is a declaration of the various types in client code, then invocation (call the "parse_line" method which takes variadic template parameters.
From there the arguments are pealed off one by one until the base/terminal case is call. Using an index ("pos") into the input string (each line of the
input file ("input.csv in this case) each data type is read and populated using stod/stof/stod or in this example a helper routine "convert" for booleans.

Template argument deduction ensures that the appropriate "convert" routine is invoked (stod,stof,stoi or any other used defined convert routine. 
Exceptions are handled and a relatively useful error message displayed.

The key point is the use of variadic templates and how type deduction helps. The main.cpp entry point shows how the above examples are handled along with other
types (just for illustration).

e.g. in main.cpp we read each line of the input file (command line arg) into "line" then handle each of these until EOF.





       switch(line[0])
         {
          // lines starting with 'N' are defined to have a string, 4 ints and a char
            case 'N':
            
               {
               
                  char c;
                  std::string symbol;
                  int user, qty, userOrderId, price;
                  // hand over to the parser
                  parse_line(2, line, ',' , user, symbol, price, qty, c, userOrderId);
                  std::cout
                        << "User: " << user
                        << ", symbol: " << symbol
                        << ", price: " << price
                        << ", qty: " << qty
                        << ", Side: \"" << c
                        << "\", userOrderId: " << userOrderId
                        << std::endl;
                  break;
               }
               // lines starting with 'C' contain just 2 ints.
             case 'C':
               {
                  int user, userOrderId;
                  // hand over to the parser
                  parse_line(2, line, ',', user, userOrderId);
                  std::cout
                        << "user: " << user
                        << ", userOrderId: "
                        << userOrderId
                        << std::endl;

                  break;
               }
               ...
               ... 
               // lines starting with 'Q' contain 2 ints, 2 doubles and a boolean
               case 'Q':
               {
                  int user, userOrderId;
                  double qty;
                  double price;
                  bool valid;
                  // hand over to the parser
                  parse_line(2, line, ',', user, userOrderId, qty, valid, price);
                  std::streamsize ss = std::cout.precision();
                  std::cout
                     << "user: " << user
                     << ", userOrderId: " << userOrderId
                     << ", qty: " << qty
                     << ", valid: " << std::boolalpha << valid
                     << ", price: " << price
                     << std::endl;
                  std::cout.precision (ss);
                  break;
               }

      
