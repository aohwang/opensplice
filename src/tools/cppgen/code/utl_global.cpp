/*
 
COPYRIGHT
 
Copyright 1992, 1993, 1994 Sun Microsystems, Inc.  Printed in the United
States of America.  All Rights Reserved.
 
This product is protected by copyright and distributed under the following
license restricting its use.
 
The Interface Definition Language Compiler Front End (CFE) is made
available for your use provided that you include this license and copyright
notice on all media and documentation and the software program in which
this product is incorporated in whole or part. You may copy and extend
functionality (but may not remove functionality) of the Interface
Definition Language CFE without charge, but you are not authorized to
license or distribute it to anyone else except as part of a product or
program developed by you or with the express written consent of Sun
Microsystems, Inc. ("Sun").
 
The names of Sun Microsystems, Inc. and any of its subsidiaries or
affiliates may not be used in advertising or publicity pertaining to
distribution of Interface Definition Language CFE as permitted herein.
 
This license is effective until terminated by Sun for failure to comply
with this license.  Upon termination, you shall destroy or return all code
and documentation for the Interface Definition Language CFE.
 
INTERFACE DEFINITION LANGUAGE CFE IS PROVIDED AS IS WITH NO WARRANTIES OF
ANY KIND INCLUDING THE WARRANTIES OF DESIGN, MERCHANTIBILITY AND FITNESS
FOR A PARTICULAR PURPOSE, NONINFRINGEMENT, OR ARISING FROM A COURSE OF
DEALING, USAGE OR TRADE PRACTICE.
 
INTERFACE DEFINITION LANGUAGE CFE IS PROVIDED WITH NO SUPPORT AND WITHOUT
ANY OBLIGATION ON THE PART OF Sun OR ANY OF ITS SUBSIDIARIES OR AFFILIATES
TO ASSIST IN ITS USE, CORRECTION, MODIFICATION OR ENHANCEMENT.
 
SUN OR ANY OF ITS SUBSIDIARIES OR AFFILIATES SHALL HAVE NO LIABILITY WITH
RESPECT TO THE INFRINGEMENT OF COPYRIGHTS, TRADE SECRETS OR ANY PATENTS BY
INTERFACE DEFINITION LANGUAGE CFE OR ANY PART THEREOF.
 
IN NO EVENT WILL SUN OR ANY OF ITS SUBSIDIARIES OR AFFILIATES BE LIABLE FOR
ANY LOST REVENUE OR PROFITS OR OTHER SPECIAL, INDIRECT AND CONSEQUENTIAL
DAMAGES, EVEN IF SUN HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 
Use, duplication, or disclosure by the government is subject to
restrictions as set forth in subparagraph (c)(1)(ii) of the Rights in
Technical Data and Computer Software clause at DFARS 252.227-7013 and FAR
52.227-19.
 
Sun, Sun Microsystems and the Sun logo are trademarks or registered
trademarks of Sun Microsystems, Inc.
 
SunSoft, Inc.  
2550 Garcia Avenue 
Mountain View, California  94043
 
NOTE:
 
SunOS, SunSoft, Sun, Solaris, Sun Microsystems or the Sun logo are
trademarks or registered trademarks of Sun Microsystems, Inc.
 
 */


// utl_global.cc - Implementation of class IDL_GlobalData
//

#include "os_stdlib.h"
#include "os_heap.h"
#include "idl.h"
#include "idl_extern.h"

// Define an increment for the size of the array used to store names of
// included files
#undef  INCREMENT
#define  INCREMENT 64

IDL_GlobalData::IDL_GlobalData()
      : pd_scopes(NULL),
      pd_root(NULL),
      pd_gen(NULL),
      pd_err(NULL),
      pd_err_count(0),
      pd_lineno(0),
      pd_filename(NULL),
      pd_main_filename(NULL),
      pd_real_filename(NULL),
      pd_in_main_file(true),
      pd_prog_name(NULL),
      pd_cpp_location(NULL),
      pd_compile_flags(0),
      pd_be(NULL),
      pd_local_escapes(NULL),
      pd_indent(NULL),
      pd_read_from_stdin(false),
      pd_warn(true),
      pd_include_file_names(NULL),
      pd_n_include_file_names(0),
      pd_n_alloced_file_names(0),
      pd_merge_includes(false),
      pd_parse_state(PS_NoState),
      pd_case_sensitive(false),
      pd_ignore_interfaces(false),
      pd_maintain_include_namespace(false)

{
   // empty
}

// Get or set scopes stack
UTL_ScopeStack *
IDL_GlobalData::scopes()
{
   return pd_scopes;
}

void
IDL_GlobalData::set_scopes(UTL_ScopeStack *s)
{
   pd_scopes = s;
}

// Get or set root of AST
AST_Root *
IDL_GlobalData::root()
{
   return pd_root;
}

void
IDL_GlobalData::set_root(AST_Root *r)
{
   pd_root = r;
}

// Get or set generator object
AST_Generator *
IDL_GlobalData::gen()
{
   return pd_gen;
}

void
IDL_GlobalData::set_gen(AST_Generator *g)
{
   pd_gen = g;
}

// Get or set error object
UTL_Error *
IDL_GlobalData::err()
{
   return pd_err;
}

void
IDL_GlobalData::set_err(UTL_Error *e)
{
   pd_err = e;
}

// Get or set error count
long
IDL_GlobalData::err_count()
{
   return pd_err_count;
}

void
IDL_GlobalData::set_err_count(long c)
{
   pd_err_count = c;
}

bool
IDL_GlobalData::warn()
{
   return pd_warn;
}

void
IDL_GlobalData::set_warn(bool warn)
{
   pd_warn = warn;
}


// Get or set line number
long
IDL_GlobalData::lineno()
{
   return pd_lineno;
}

void
IDL_GlobalData::set_lineno(long n)
{
   pd_lineno = n;
}

// Get or set file name being read now
UTL_String *
IDL_GlobalData::filename()
{
   return pd_filename;
}

void
IDL_GlobalData::set_filename(UTL_String *f)
{
   pd_filename = f;
}

// Get or set main file name
UTL_String *
IDL_GlobalData::main_filename()
{
   return pd_main_filename;
}

void
IDL_GlobalData::set_main_filename(UTL_String *n)
{
   pd_main_filename = n;
}

// Get or set real file name
UTL_String *
IDL_GlobalData::real_filename()
{
   return pd_real_filename;
}// Store a name of an #include file

void
IDL_GlobalData::set_real_filename(UTL_String *n)
{
   pd_real_filename = n;
}

// Get or set indicator whether import is on
bool
IDL_GlobalData::imported()
{
   if (pd_merge_includes)
      return false;
   else if (pd_in_main_file)
      return false;
   else
      return pd_import;
}

bool
IDL_GlobalData::import()
{
   return pd_import;
}

void
IDL_GlobalData::set_import(bool is_in)
{
   pd_import = is_in;
}

// Get or set indicator whether we're reading the main file now
bool
IDL_GlobalData::in_main_file()
{
   return pd_in_main_file;
}

void
IDL_GlobalData::set_in_main_file(bool is_in)
{
   pd_in_main_file = is_in;
}

// Get or set stripped file name
UTL_String *
IDL_GlobalData::stripped_filename()
{
   return pd_stripped_filename;
}

void
IDL_GlobalData::set_stripped_filename(UTL_String *nm)
{
   pd_stripped_filename = nm;
}

// Get or set cache value for argv[0]
char *
IDL_GlobalData::prog_name()
{
   return pd_prog_name;
}

void
IDL_GlobalData::set_prog_name(char *pn)
{
   pd_prog_name = pn;// Store a name of an #include file
}

// Get or set location to find C preprocessor
char *
IDL_GlobalData::cpp_location()
{
   return pd_cpp_location;
}

void
IDL_GlobalData::set_cpp_location(char *l)
{
   pd_cpp_location = l;
}

// Get or set IDL compiler flags
long
IDL_GlobalData::compile_flags()
{
   return pd_compile_flags;
}

void
IDL_GlobalData::set_compile_flags(long cf)
{
   pd_compile_flags = cf;
}

bool
IDL_GlobalData::IncludeFileMerge()
{
   return pd_merge_includes;
}

void
IDL_GlobalData::IncludeFileMerge(bool yes_or_no)
{
   pd_compile_flags = (yes_or_no) ? pd_compile_flags | IDL_CF_NOIMPORT
                      : pd_compile_flags & (~IDL_CF_NOIMPORT);
   pd_merge_includes = yes_or_no;
}

// Get or set BE to be used
const char *IDL_GlobalData::be()
{
   return pd_be;
}

void
IDL_GlobalData::set_be(const char *nbe)
{
   pd_be = nbe;
}

// Get or set local escapes string. This provides additional mechanism
// to pass information to a BE.
char *IDL_GlobalData::local_escapes()
{
   return pd_local_escapes;
}

void
IDL_GlobalData::set_local_escapes(char *e)
{
   pd_local_escapes = e;
}

// Get or set indent object
UTL_Indenter *
IDL_GlobalData::indent()
{
   return pd_indent;
}

void
IDL_GlobalData::set_indent(UTL_Indenter *i)
{
   pd_indent = i;
}

// Get or set indicator whether we're reading from stdin
bool
IDL_GlobalData::read_from_stdin()
{
   return pd_read_from_stdin;
}

void
IDL_GlobalData::set_read_from_stdin(bool r)
{
   pd_read_from_stdin = r;
}

// Have we seen this include file name before?
long
IDL_GlobalData::seen_include_file_before(UTL_String *n)
{
   unsigned long i;

   for (i = 0; i < pd_n_include_file_names; i++)
      if (n->compare(pd_include_file_names[i]))
         return true;

   return false;
}

// Store a name of an #include file
void
IDL_GlobalData::store_include_file_name(UTL_String *n)
{
   UTL_String **o_include_file_names;
   unsigned long o_n_alloced_file_names, i;

   /*
    * Check if we need to store it at all or whether we've seen it already
    */

   if (seen_include_file_before(n))
      return ;

   /*
    * OK, need to store. Make sure there's space for one more string
    */
   if (pd_n_include_file_names == pd_n_alloced_file_names)
   {
      if (pd_n_alloced_file_names == 0)
      {
         pd_n_alloced_file_names = INCREMENT;
         pd_include_file_names = new UTL_String * [pd_n_alloced_file_names];
      }
      else
      {
         o_include_file_names = pd_include_file_names;
         o_n_alloced_file_names = pd_n_alloced_file_names;
         pd_n_alloced_file_names += INCREMENT;
         pd_include_file_names = new UTL_String * [pd_n_alloced_file_names];

         for (i = 0; i < o_n_alloced_file_names; i++)
            pd_include_file_names[i] = o_include_file_names[i];

         delete [] o_include_file_names;
      }
   }

   /*
    * Store it
    */
   pd_include_file_names[pd_n_include_file_names++] = n;
}

void
IDL_GlobalData::set_include_file_names(UTL_String **ns)
{
   pd_include_file_names = ns;
}

UTL_String **
IDL_GlobalData::include_file_names()
{
   return pd_include_file_names;
}

void
IDL_GlobalData::set_n_include_file_names(unsigned long n)
{
   pd_n_include_file_names = n;
}

unsigned long
IDL_GlobalData::n_include_file_names()
{
   return pd_n_include_file_names;
}

void
IDL_GlobalData::set_parse_state(ParseState ps)
{
   pd_parse_state = ps;
}

IDL_GlobalData::ParseState
IDL_GlobalData::parse_state()
{
   return pd_parse_state;
}

void
IDL_GlobalData::set_compilation_stage(CompilationStage cs)
{
   pd_compilation_stage = cs;
}

IDL_GlobalData::CompilationStage
IDL_GlobalData::compilation_stage()
{
   return pd_compilation_stage;
}

void
IDL_GlobalData::set_case_sensitive(bool val)
{
   pd_case_sensitive = val;
}

bool
IDL_GlobalData::case_sensitive()
{
   return pd_case_sensitive;
}

void
IDL_GlobalData::set_ignore_interfaces(bool val)
{
   pd_ignore_interfaces = val;
}

bool
IDL_GlobalData::ignore_interfaces()
{
   return pd_ignore_interfaces;
}

void
IDL_GlobalData::set_maintain_include_namespace(bool val)
{
    pd_maintain_include_namespace = val;
}

bool
IDL_GlobalData::maintain_include_namespace()
{
   return pd_maintain_include_namespace;
}

/*
 * Convert a PredefinedType to an ExprType
 */
AST_Expression::ExprType
IDL_GlobalData::PredefinedTypeToExprType(AST_PredefinedType::PredefinedType pt)
{
   switch (pt)
   {

         case AST_PredefinedType::PT_long:
         return AST_Expression::EV_long;

         case AST_PredefinedType::PT_ulong:
         return AST_Expression::EV_ulong;

         case AST_PredefinedType::PT_longlong:
         return AST_Expression::EV_longlong;

         case AST_PredefinedType::PT_ulonglong:
         return AST_Expression::EV_ulonglong;

         case AST_PredefinedType::PT_short:
         return AST_Expression::EV_short;

         case AST_PredefinedType::PT_ushort:
         return AST_Expression::EV_ushort;

         case AST_PredefinedType::PT_float:
         return AST_Expression::EV_float;

         case AST_PredefinedType::PT_double:
         return AST_Expression::EV_double;

         case AST_PredefinedType::PT_char:
         return AST_Expression::EV_char;

         case AST_PredefinedType::PT_wchar:
         return AST_Expression::EV_wchar;

         case AST_PredefinedType::PT_octet:
         return AST_Expression::EV_octet;

         case AST_PredefinedType::PT_boolean:
         return AST_Expression::EV_bool;

         default:
         return AST_Expression::EV_any;
   }
}

bool IDL_GlobalData::valid_identifier (const char *id)
{
   // Object, any and abstract deliberately missing from idl_keywords
   static const char *idl_keywords[] =
   {
      "exception", "inout", "provides", "truncatable",
      "emits", "interface", "public", "typedef",
      "attribute", "enum", "local", "publishes", "typeid",
      "boolean", "eventtype", "long", "raises", "typeprefix",
      "case", "factory", "module", "readonly", "unsigned",
      "char", "false", "multiple", "setraises", "union",
      "component", "finder", "native", "sequence", "uses",
      "const", "fixed", "short", "ValueBase",
      "consumes", "float", "octet", "string", "valuetype",
      "context", "getraises", "oneway", "struct", "void",
      "custom", "home", "out", "supports", "wchar",
      "default", "import", "primarykey", "switch", "wstring",
      "double", "in", "private", "true",
      NULL
   };

   char *id1 = os_strdup (id);
   char *tmp = id1;
   bool result = true;

   while (*tmp)
   {
      *tmp = tolower (*tmp);
      tmp++;
   }

   for (int i = 0; idl_keywords[i] != NULL; i++)
   {
      if (strcmp (id1, idl_keywords[i]) == 0)
      {
         err ()->illegal_identifier (id);
         result = false;
         break;
      }
   }

   os_free (id1);
   return result;
}
