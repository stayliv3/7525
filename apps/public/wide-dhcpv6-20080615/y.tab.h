/* A Bison parser, made by GNU Bison 1.875c.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INTERFACE = 258,
     IFNAME = 259,
     PREFIX_INTERFACE = 260,
     SLA_ID = 261,
     SLA_LEN = 262,
     DUID_ID = 263,
     ID_ASSOC = 264,
     IA_PD = 265,
     IAID = 266,
     IA_NA = 267,
     ADDRESS = 268,
     REQUEST = 269,
     SEND = 270,
     ALLOW = 271,
     PREFERENCE = 272,
     HOST = 273,
     HOSTNAME = 274,
     DUID = 275,
     OPTION = 276,
     RAPID_COMMIT = 277,
     DNS_SERVERS = 278,
     DNS_NAME = 279,
     VENDOR_OPTS = 280,
     DSLITE_NAME = 281,
     DSLITE_ADDRESS = 282,
     NTP_SERVERS = 283,
     REFRESHTIME = 284,
     SIP_SERVERS = 285,
     SIP_NAME = 286,
     NIS_SERVERS = 287,
     NIS_NAME = 288,
     NISP_SERVERS = 289,
     NISP_NAME = 290,
     BCMCS_SERVERS = 291,
     BCMCS_NAME = 292,
     INFO_ONLY = 293,
     SCRIPT = 294,
     DELAYEDKEY = 295,
     AUTHENTICATION = 296,
     PROTOCOL = 297,
     ALGORITHM = 298,
     DELAYED = 299,
     RECONFIG = 300,
     HMACMD5 = 301,
     MONOCOUNTER = 302,
     AUTHNAME = 303,
     RDM = 304,
     KEY = 305,
     KEYINFO = 306,
     REALM = 307,
     KEYID = 308,
     SECRET = 309,
     KEYNAME = 310,
     EXPIRE = 311,
     ADDRPOOL = 312,
     POOLNAME = 313,
     RANGE = 314,
     TO = 315,
     ADDRESS_POOL = 316,
     INCLUDE = 317,
     NUMBER = 318,
     SLASH = 319,
     EOS = 320,
     BCL = 321,
     ECL = 322,
     STRING = 323,
     QSTRING = 324,
     PREFIX = 325,
     INFINITY = 326,
     COMMA = 327
   };
#endif
#define INTERFACE 258
#define IFNAME 259
#define PREFIX_INTERFACE 260
#define SLA_ID 261
#define SLA_LEN 262
#define DUID_ID 263
#define ID_ASSOC 264
#define IA_PD 265
#define IAID 266
#define IA_NA 267
#define ADDRESS 268
#define REQUEST 269
#define SEND 270
#define ALLOW 271
#define PREFERENCE 272
#define HOST 273
#define HOSTNAME 274
#define DUID 275
#define OPTION 276
#define RAPID_COMMIT 277
#define DNS_SERVERS 278
#define DNS_NAME 279
#define VENDOR_OPTS 280
#define DSLITE_NAME 281
#define DSLITE_ADDRESS 282
#define NTP_SERVERS 283
#define REFRESHTIME 284
#define SIP_SERVERS 285
#define SIP_NAME 286
#define NIS_SERVERS 287
#define NIS_NAME 288
#define NISP_SERVERS 289
#define NISP_NAME 290
#define BCMCS_SERVERS 291
#define BCMCS_NAME 292
#define INFO_ONLY 293
#define SCRIPT 294
#define DELAYEDKEY 295
#define AUTHENTICATION 296
#define PROTOCOL 297
#define ALGORITHM 298
#define DELAYED 299
#define RECONFIG 300
#define HMACMD5 301
#define MONOCOUNTER 302
#define AUTHNAME 303
#define RDM 304
#define KEY 305
#define KEYINFO 306
#define REALM 307
#define KEYID 308
#define SECRET 309
#define KEYNAME 310
#define EXPIRE 311
#define ADDRPOOL 312
#define POOLNAME 313
#define RANGE 314
#define TO 315
#define ADDRESS_POOL 316
#define INCLUDE 317
#define NUMBER 318
#define SLASH 319
#define EOS 320
#define BCL 321
#define ECL 322
#define STRING 323
#define QSTRING 324
#define PREFIX 325
#define INFINITY 326
#define COMMA 327




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 126 "cfparse.y"
typedef union YYSTYPE {
	long long num;
	char* str;
	struct cf_list *list;
	struct dhcp6_prefix *prefix;
	struct dhcp6_range *range;
	struct dhcp6_poolspec *pool;
} YYSTYPE;
/* Line 1275 of yacc.c.  */
#line 190 "y.tab.h"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;



