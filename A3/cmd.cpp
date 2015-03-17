// ============================================================================
// cmd.cpp
// ~~~~~~~
// author : Samina Khan
// - implement the two main commands: validate and display
// - this is the only file you can modify and submit
// ============================================================================

#include <iostream>
#include <sstream>
#include <stack>
#include <map>

#include "cmd.h"
#include "Lexer.h" // you should make use of the provided Lexer
#include "term_control.h"
#include "error_handling.h"

#include <set>

using namespace std;

/**
 * -----------------------------------------------------------------------------
 *  TO BE IMPLEMENTED BY YOU
 *  check whether the given expression is well-formed and print it out
 *  - if it is NOT well-formed, return one of the three error messages:
 *     "INVALID TOKEN"
 *     "EXPRESSION NOT WELL-FORMED"
 *     "UNKNOWN TAG"
 *  - if it is well-formed, return the string to be printed, with control codes
 *    inserted properly at the right places 
 * -----------------------------------------------------------------------------
 */
string display(const string& expression) 
{
	Lexer myLexer;
	string result = "";

	//color map
	map<string, term_colors_t> color_map;
	color_map["red"] = RED;
	color_map["green"] = GREEN;
	color_map["yellow"] = YELLOW;
	color_map["blue"] = BLUE;
	color_map["magenta"] = MAGENTA;
	color_map["cyan"] = CYAN;

	//stack for colors
	stack<string> colorStack;

	//attribute map
	map<string, term_attrib_t> attrib_map;
	attrib_map["dim"] = DIM;
	attrib_map["underline"] = UNDERLINE;
	attrib_map["bright"] = BRIGHT;
	//stack for attributes
	stack<string> attribStack;

	myLexer.set_input(expression);

	//keep track of most recent tag category/stack
	stack<string> currentTag;

	//keep track of current active attribs
	set<string> attribSet;

	while(myLexer.has_more_token()){

		Token tok = myLexer.next_token();

		switch(tok.type){
			case TAG:
				if(tok.value[0] !='/'){ //OPEN TAGS
					
					//colors
					if(color_map.find(tok.value) != color_map.end()){
						result.append(term_fg(color_map[tok.value]));
						colorStack.push(tok.value);
						currentTag.push(tok.value);
						break;
					}
					//attributes
					else if(attrib_map.find(tok.value) != attrib_map.end()){
						result.append(term_attrib(attrib_map[tok.value]));
						attribStack.push(tok.value);
						currentTag.push(tok.value);
						attribSet.insert(tok.value);
						break;
					}
					//unknown tag
					else{
						return "UNKNOWN TAG";
					}
					
				}
				else{ //CLOSE TAG
					tok.value.erase(0, 1);

					//colors
					if(color_map.find(tok.value) != color_map.end()){
						if(!colorStack.empty() && tok.value == colorStack.top() && tok.value == currentTag.top()){
							colorStack.pop();
							currentTag.pop();
							if(!colorStack.empty()){
								result.append(term_fg(color_map[colorStack.top()]));
								break;
							}
							else{
								result.append(term_fg(DEFAULT_COLOR));
								break;
							}
							
						}
						else{
							return "EXPRESSION NOT WELL-FORMED";
						}
						break;
					}
					//attributes
					else if(attrib_map.find(tok.value) != attrib_map.end()){
						if(!attribStack.empty() && tok.value == attribStack.top() && tok.value == currentTag.top()){
							attribStack.pop();
							currentTag.pop();
							attribSet.erase(tok.value);

							if(!attribStack.empty()){
								result.append(term_attrib());
								if(!colorStack.empty()){
									result.append(term_fg(color_map[colorStack.top()]));
								}
								for(set<string>::iterator it = attribSet.begin(); it != attribSet.end(); ++it){
									result.append(term_attrib(attrib_map[*it]));
								}
								break;
							}
							else{
								result.append(term_attrib());
								if(!colorStack.empty()){
									result.append(term_fg(color_map[colorStack.top()]));
									break;
								}
								break;
							}
							break;							
						}
						else{
							return "EXPRESSION NOT WELL-FORMED";
						}
						break;
					}
					//unknown tag
					else{
						return "UNKNOWN TAG";
					}
							
				}

			case IDENT:
				result.append(tok.value);
				break;

			case BLANK:
				result.append(tok.value);
				break;

			case ERRTOK:
				return "INVALID TOKEN";

			default:
				break;
		}

	}

	if(!colorStack.empty() || !attribStack.empty()){
		return "EXPRESSION NOT WELL-FORMED";
	}
    return result;
}

/**
 * -----------------------------------------------------------------------------
 *  TO BE IMPLEMENTED BY YOU
 *  check whether the given expression is well-formed
 *  - if it is NOT well-formed, return one of the three error messages:
 *     "INVALID TOKEN"
 *     "EXPRESSION NOT WELL-FORMED"
 *     "UNKNOWN TAG"
 *  - if it is well-formed, return "VALID"
 * -----------------------------------------------------------------------------
 */
string validate(const string& expression)
{
	Lexer myLexer;

	//color map
	map<string, term_colors_t> color_map;
	color_map["red"] = RED;
	color_map["green"] = GREEN;
	color_map["yellow"] = YELLOW;
	color_map["blue"] = BLUE;
	color_map["magenta"] = MAGENTA;
	color_map["cyan"] = CYAN;

	//stack for colors
	stack<string> colorStack;

	//attribute map
	map<string, term_attrib_t> attrib_map;
	attrib_map["dim"] = DIM;
	attrib_map["underline"] = UNDERLINE;
	attrib_map["bright"] = BRIGHT;
	//stack for attributes
	stack<string> attribStack;

	myLexer.set_input(expression);

	//keep track of most recent tag category/stack
	stack<string> currentTag;

	while(myLexer.has_more_token()){

		Token tok = myLexer.next_token();

		switch(tok.type){
			case TAG:
				if(tok.value[0] !='/'){ //OPEN TAGS
					
					//colors
					if(color_map.find(tok.value) != color_map.end()){
						colorStack.push(tok.value);
						currentTag.push(tok.value);
						break;
					}
					//attributes
					else if(attrib_map.find(tok.value) != attrib_map.end()){
						attribStack.push(tok.value);
						currentTag.push(tok.value);
						break;
					}
					//unknown tag
					else{
						return "UNKNOWN TAG";
					}
					
				}
				else{ //CLOSE TAG
					tok.value.erase(0, 1);

					//colors
					if(color_map.find(tok.value) != color_map.end()){
						if(!colorStack.empty() && tok.value == colorStack.top() && tok.value == currentTag.top()){
							colorStack.pop();
							currentTag.pop();							
						}
						else{
							return "EXPRESSION NOT WELL-FORMED";
						}
						break;
					}
					//attributes
					else if(attrib_map.find(tok.value) != attrib_map.end()){
						if(!attribStack.empty() && tok.value == attribStack.top() && tok.value == currentTag.top()){
							attribStack.pop();
							currentTag.pop();

							break;							
						}
						else{
							return "EXPRESSION NOT WELL-FORMED";
						}
						break;
					}
					//unknown tag
					else{
						return "UNKNOWN TAG";
					}
							
				}

			case IDENT:
				break;

			case BLANK:
				break;

			case ERRTOK:
				return "INVALID TOKEN";

			default:
				break;
		}

	}

	if(!colorStack.empty() || !attribStack.empty() || !currentTag.empty()){
		return "EXPRESSION NOT WELL-FORMED";
	}
    return "VALID";
}