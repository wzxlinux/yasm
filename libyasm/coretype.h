/**
 * \file libyasm/coretype.h
 * \brief YASM core types and utility functions.
 *
 * \rcs
 * $Id$
 * \endrcs
 *
 * \license
 *  Copyright (C) 2001  Peter Johnson
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND OTHER CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR OTHER CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 * \endlicense
 */
#ifndef YASM_CORETYPE_H
#define YASM_CORETYPE_H

/** Architecture instance (mostly opaque type).  \see arch.h for details. */
typedef struct yasm_arch yasm_arch;
/** Preprocessor interface.  \see preproc.h for details. */
typedef struct yasm_preproc yasm_preproc;
/** Parser instance (mostly opaque type).  \see parser.h for details. */
typedef struct yasm_parser yasm_parser;
/** Optimizer interface.  \see optimizer.h for details. */
typedef struct yasm_optimizer yasm_optimizer;
/** Object format interface.  \see objfmt.h for details. */
typedef struct yasm_objfmt yasm_objfmt;
/** Debug format interface.  \see dbgfmt.h for details. */
typedef struct yasm_dbgfmt yasm_dbgfmt;
/** List format interface.  \see listfmt.h for details. */
typedef struct yasm_listfmt yasm_listfmt;

/** YASM associated data callback structure.  Many data structures can have
 * arbitrary data associated with them.
 */
typedef struct yasm_assoc_data_callback {
    /** Free memory allocated for associated data.
     * \param data	associated data
     */
    void (*destroy) (/*@only@*/ void *data);

    /** Print a description of allocated data.  For debugging purposes.
     * \param data		associated data
     * \param f			output file
     * \param indent_level	indentation level
     */
    void (*print) (void *data, FILE *f, int indent_level);
} yasm_assoc_data_callback;

/** Bytecode (opaque type).
 * \see bytecode.h for related functions.
 * Define YASM_BC_INTERNAL to get visible internals.
 */
typedef struct yasm_bytecode yasm_bytecode;

/** Object (opaque type).  \see section.h for related functions. */
typedef struct yasm_object yasm_object;

/** Section (opaque type).  \see section.h for related functions. */
typedef struct yasm_section yasm_section;

/** Symbol table (opaque type).  \see symrec.h for related functions. */
typedef struct yasm_symtab yasm_symtab;

/** Symbol record (opaque type).  \see symrec.h for related functions. */
typedef struct yasm_symrec yasm_symrec;

/** Expression (opaque type).
 * \see expr.h for related functions.
 * Define YASM_EXPR_INTERNAL to get visible internals.
 */
typedef struct yasm_expr yasm_expr;
/** Integer value (opaque type).  \see intnum.h for related functions. */
typedef struct yasm_intnum yasm_intnum;
/** Floating point value (opaque type).
 * \see floatnum.h for related functions.
 */
typedef struct yasm_floatnum yasm_floatnum;

/** Line number mapping repository (opaque type).  \see linemgr.h for related
 * functions.
 */
typedef struct yasm_linemap yasm_linemap;

/** Value/parameter pair (opaque type).
 * \see valparam.h for related functions.
 */
typedef struct yasm_valparam yasm_valparam;
/** List of value/parameters (opaque type).
 * \see valparam.h for related functions.
 */
typedef struct yasm_valparamhead yasm_valparamhead;

/** A list of instruction operands (opaque type).
 * The list goes from left-to-right as parsed.
 * \see arch.h for related functions.
 */
typedef struct yasm_insn_operands yasm_insn_operands;

/** Expression operators usable in #yasm_expr expressions. */
typedef enum {
    YASM_EXPR_IDENT,	/**< No operation, just a value. */
    YASM_EXPR_ADD,	/**< Arithmetic addition (+). */
    YASM_EXPR_SUB,	/**< Arithmetic subtraction (-). */
    YASM_EXPR_MUL,	/**< Arithmetic multiplication (*). */
    YASM_EXPR_DIV,	/**< Arithmetic unsigned division. */
    YASM_EXPR_SIGNDIV,	/**< Arithmetic signed division. */
    YASM_EXPR_MOD,	/**< Arithmetic unsigned modulus. */
    YASM_EXPR_SIGNMOD,	/**< Arithmetic signed modulus. */
    YASM_EXPR_NEG,	/**< Arithmetic negation (-). */
    YASM_EXPR_NOT,	/**< Bitwise negation. */
    YASM_EXPR_OR,	/**< Bitwise OR. */
    YASM_EXPR_AND,	/**< Bitwise AND. */
    YASM_EXPR_XOR,	/**< Bitwise XOR. */
    YASM_EXPR_NOR,	/**< Bitwise NOR. */
    YASM_EXPR_SHL,	/**< Shift left (logical). */
    YASM_EXPR_SHR,	/**< Shift right (logical). */
    YASM_EXPR_LOR,	/**< Logical OR. */
    YASM_EXPR_LAND,	/**< Logical AND. */
    YASM_EXPR_LNOT,	/**< Logical negation. */
    YASM_EXPR_LT,	/**< Less than comparison. */
    YASM_EXPR_GT,	/**< Greater than comparison. */
    YASM_EXPR_EQ,	/**< Equality comparison. */
    YASM_EXPR_LE,	/**< Less than or equal to comparison. */
    YASM_EXPR_GE,	/**< Greater than or equal to comparison. */
    YASM_EXPR_NE,	/**< Not equal comparison. */
    YASM_EXPR_NONNUM,	/**< Start of non-numeric operations (not an op). */
    YASM_EXPR_SEG,	/**< SEG operator (gets segment portion of address). */
    YASM_EXPR_WRT,	/**< WRT operator (gets offset of address relative to
			 *   some other segment). */
    YASM_EXPR_SEGOFF	/**< The ':' in segment:offset. */
} yasm_expr_op;

/** Symbol record visibility.
 * \see symrec.h for related functions.
 * \note YASM_SYM_EXTERN and YASM_SYM_COMMON are mutually exclusive.
 */
typedef enum {
    YASM_SYM_LOCAL = 0,		/**< Default, local only */
    YASM_SYM_GLOBAL = 1 << 0,	/**< If symbol is declared GLOBAL */
    YASM_SYM_COMMON = 1 << 1,	/**< If symbol is declared COMMON */
    YASM_SYM_EXTERN = 1 << 2,	/**< If symbol is declared EXTERN */
    YASM_SYM_DLOCAL = 1 << 3	/**< If symbol is explicitly declared LOCAL */
} yasm_sym_vis;

/** Determine the distance between the starting offsets of two bytecodes.
 * \param precbc1	preceding bytecode to the first bytecode
 * \param precbc2	preceding bytecode to the second bytecode
 * \return Distance in bytes between the two bytecodes (bc2-bc1), or NULL if
 *	   the distance was indeterminate.
 */
typedef /*@null@*/ yasm_intnum * (*yasm_calc_bc_dist_func)
    (yasm_bytecode *precbc1, yasm_bytecode *precbc2);

/** Convert yasm_expr to its byte representation.  Usually implemented by
 * object formats to keep track of relocations and verify legal expressions.
 * Must put the value into the least significant bits of the destination,
 * unless shifted into more significant bits by the shift parameter.  The
 * destination bits must be cleared before being set.
 * \param ep		(double) pointer to expression
 * \param buf		buffer for byte representation
 * \param destsize	destination size (in bytes)
 * \param valsize	size (in bits)
 * \param shift		left shift (in bits); may be negative to specify right
 *			shift (standard warnings include truncation to boundary)
 * \param offset	offset (in bytes) of the expr contents from the start
 *			of the bytecode (sometimes needed for conditional jumps)
 * \param bc		current bytecode (usually passed into higher-level
 *			calling function)
 * \param rel		if nonzero, expr should be treated as PC/IP-relative
 * \param warn		enables standard warnings: zero for none;
 *			nonzero for overflow/underflow floating point warnings;
 *			negative for signed integer warnings,
 *			positive for unsigned integer warnings
 * \param d		objfmt-specific data (passed into higher-level calling
 *			function)
 * \return Nonzero if an error occurred, 0 otherwise.
 */
typedef int (*yasm_output_expr_func)
    (yasm_expr **ep, /*@out@*/ unsigned char *buf, size_t destsize,
     size_t valsize, int shift, unsigned long offset, yasm_bytecode *bc,
     int rel, int warn, /*@null@*/ void *d) /*@uses *ep@*/;

/** Convert a symbol reference to its byte representation.  Usually implemented
 * by object formats and debug formats to keep track of relocations generated
 * by themselves.
 * \param sym		symbol
 * \param bc		current bytecode (usually passed into higher-level
 *			calling function)
 * \param buf		buffer for byte representation
 * \param destsize	destination size (in bytes)
 * \param valsize	size (in bits)
 * \param warn		enables standard warnings: zero for none;
 *			nonzero for overflow/underflow floating point warnings;
 *			negative for signed integer warnings,
 *			positive for unsigned integer warnings
 * \param d		objfmt-specific data (passed into higher-level calling
 *			function)
 * \return Nonzero if an error occurred, 0 otherwise.
 */
typedef int (*yasm_output_reloc_func)
    (yasm_symrec *sym, yasm_bytecode *bc, unsigned char *buf, size_t destsize,
     size_t valsize, int warn, void *d);

/** Sort an array using merge sort algorithm.
 * \internal
 * \param base	    base of array
 * \param nmemb	    number of elements in array
 * \param size	    size of each array element
 * \param compar    element comparison function
 */
int yasm__mergesort(void *base, size_t nmemb, size_t size,
		    int (*compar)(const void *, const void *));

/** Separate string by delimiters.
 * \internal
 * \param stringp   string
 * \param delim	    set of 1 or more delimiters
 * \return First/next substring.
 */
/*@null@*/ char *yasm__strsep(char **stringp, const char *delim);

/** Compare two strings, ignoring case differences.
 * \internal
 * \param s1	string 1
 * \param s2	string 2
 * \return 0 if strings are equal, -1 if s1<s2, 1 if s1>s2.
 */
int yasm__strcasecmp(const char *s1, const char *s2);

/** Compare portion of two strings, ignoring case differences.
 * \internal
 * \param s1	string 1
 * \param s2	string 2
 * \param n	maximum number of characters to compare
 * \return 0 if strings are equal, -1 if s1<s2, 1 if s1>s2.
 */
int yasm__strncasecmp(const char *s1, const char *s2, size_t n);

/** Split a UNIX pathname into head (directory) and tail (base filename)
 * portions.
 * \internal
 * \param path	pathname
 * \param tail	(returned) base filename
 * \return Length of head (directory).
 */
size_t yasm__splitpath_unix(const char *path, /*@out@*/ const char **tail);

/** Split a Windows pathname into head (directory) and tail (base filename)
 * portions.
 * \internal
 * \param path	pathname
 * \param tail	(returned) base filename
 * \return Length of head (directory).
 */
size_t yasm__splitpath_win(const char *path, /*@out@*/ const char **tail);

#ifndef yasm__splitpath
/** Split a pathname into head (directory) and tail (base filename) portions.
 * Unless otherwise defined, defaults to yasm__splitpath_unix().
 * \internal
 * \param path	pathname
 * \param head	(returned) directory
 * \return Length of head (directory).
 */
#define yasm__splitpath(path, tail)	yasm__splitpath_unix(path, tail)
#endif

/** strdup() implementation using yasm_xmalloc().
 * \internal
 * \param str	string
 * \return Newly allocated duplicate string.
 */
/*@only@*/ char *yasm__xstrdup(const char *str);

/** strndup() implementation using yasm_xmalloc().
 * \internal
 * \param str	string
 * \param len	maximum number of characters to copy
 * \return Newly allocated duplicate string.
 */
/*@only@*/ char *yasm__xstrndup(const char *str, size_t len);

/** Error-checking memory allocation.  A default implementation is provided
 * that calls yasm_fatal() on allocation errors.
 * A replacement should \em never return NULL.
 * \param size	    number of bytes to allocate
 * \return Allocated memory block.
 */
extern /*@only@*/ /*@out@*/ void * (*yasm_xmalloc) (size_t size);

/** Error-checking memory allocation (with clear-to-0).  A default
 * implementation is provided that calls yasm_fatal() on allocation errors.
 * A replacement should \em never return NULL.
 * \param size	    number of elements to allocate
 * \param elsize    size (in bytes) of each element
 * \return Allocated and cleared memory block.
 */
extern /*@only@*/ void * (*yasm_xcalloc) (size_t nelem, size_t elsize);

/** Error-checking memory reallocation.  A default implementation is provided
 * that calls yasm_fatal() on allocation errors.  A replacement should
 * \em never return NULL.
 * \param oldmem    memory block to resize
 * \param elsize    new size, in bytes
 * \return Re-allocated memory block.
 */
extern /*@only@*/ void * (*yasm_xrealloc)
    (/*@only@*/ /*@out@*/ /*@returned@*/ /*@null@*/ void *oldmem, size_t size)
    /*@modifies oldmem@*/;

/** Error-checking memory deallocation.  A default implementation is provided
 * that calls yasm_fatal() on allocation errors.
 * \param p	memory block to free
 */
extern void (*yasm_xfree) (/*@only@*/ /*@out@*/ /*@null@*/ void *p)
    /*@modifies p@*/;

#endif
