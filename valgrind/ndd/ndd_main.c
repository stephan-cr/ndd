
/*--------------------------------------------------------------------*/
/*--- NDD: The minimal Valgrind null dereference checker           ---*/
/*--------------------------------------------------------------------*/

/*
   This file is part of NDD, the minimal Valgrind null dereference checker.

   Copyright (C) 2010, 2011 Stephan Creutz

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307, USA.

   The GNU General Public License is contained in the file COPYING.
*/

#include "pub_tool_basics.h"
#include "pub_tool_libcassert.h"
#include "pub_tool_libcprint.h"
#include "pub_tool_stacktrace.h"
#include "pub_tool_threadstate.h"
#include "pub_tool_tooliface.h"

static void ndd_post_clo_init(void)
{
}

static void check_load_addr(Addr addr)
{
  if (addr == 0) {
    VG_(message)(Vg_UserMsg, "load from null pointer detected\n");
    VG_(get_and_pp_StackTrace)(VG_(get_running_tid)(), 16);
    VG_(exit)(1);
  }
}

static
IRSB* ndd_instrument(VgCallbackClosure* closure,
                    IRSB* bb,
                    VexGuestLayout* layout,
                    VexGuestExtents* vge,
                    IRType gWordTy, IRType hWordTy)
{
  if (gWordTy != hWordTy)
    VG_(tool_panic)("host/guest word size mismatch");

  IRSB *new_bb = deepCopyIRSBExceptStmts(bb);

  Int i = 0;
  for (; i < bb->stmts_used && bb->stmts[i]->tag != Ist_IMark; i++)
    addStmtToIRSB(new_bb, bb->stmts[i]);

  for (; i < bb->stmts_used; i++) {
    IRStmt *st = bb->stmts[i];
    tl_assert(st);

    if (st->tag == Ist_WrTmp) {
      IRExpr *e = st->Ist.WrTmp.data;
      tl_assert(e);
      if (e->tag == Iex_Load) {
        IRExpr *addr_expr = e->Iex.Load.addr;
        IRDirty *ir_dirty = unsafeIRDirty_0_N(0, "check_load_addr",
                                              check_load_addr,
                                              mkIRExprVec_1(addr_expr));
        addStmtToIRSB(new_bb, IRStmt_Dirty(ir_dirty));
      }
    }

    addStmtToIRSB(new_bb, st);
  }

  return new_bb;
}

static void ndd_fini(Int exitcode)
{
}

static void ndd_pre_clo_init(void)
{
   VG_(details_name)            ("NDD");
   VG_(details_version)         ("0.1");
   VG_(details_description)     ("a minimal null dereference checker");
   VG_(details_copyright_author)(
       "Copyright (C) 2010, 2011, and GNU GPL'd, by Stephan Creutz.");
   VG_(details_bug_reports_to)  ("https://bitbucket.org/stephan_cr/ndd/");

   VG_(basic_tool_funcs)        (ndd_post_clo_init,
                                 ndd_instrument,
                                 ndd_fini);

   /* No needs, no core events to track */
}

VG_DETERMINE_INTERFACE_VERSION(ndd_pre_clo_init)

/*--------------------------------------------------------------------*/
/*--- end                                                          ---*/
/*--------------------------------------------------------------------*/
