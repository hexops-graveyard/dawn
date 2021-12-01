// Copyright 2021 The Tint Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "src/resolver/resolver.h"

#include "gmock/gmock.h"
#include "src/resolver/resolver_test_helper.h"
#include "src/sem/block_statement.h"
#include "src/sem/for_loop_statement.h"
#include "src/sem/if_statement.h"
#include "src/sem/loop_statement.h"
#include "src/sem/switch_statement.h"

namespace tint {
namespace resolver {
namespace {

using ResolverCompoundStatementTest = ResolverTest;

TEST_F(ResolverCompoundStatementTest, FunctionBlock) {
  // fn F() {
  //   var x : 32;
  // }
  auto* stmt = Decl(Var("x", ty.i32()));
  auto* f = Func("F", {}, ty.void_(), {stmt});

  ASSERT_TRUE(r()->Resolve()) << r()->error();

  auto* s = Sem().Get(stmt);
  ASSERT_NE(s, nullptr);
  ASSERT_NE(s->Block(), nullptr);
  ASSERT_TRUE(s->Block()->Is<sem::FunctionBlockStatement>());
  EXPECT_EQ(s->Block(), s->FindFirstParent<sem::BlockStatement>());
  EXPECT_EQ(s->Block(), s->FindFirstParent<sem::FunctionBlockStatement>());
  EXPECT_EQ(s->Function()->Declaration(), f);
  EXPECT_EQ(s->Block()->Parent(), nullptr);
}

TEST_F(ResolverCompoundStatementTest, Block) {
  // fn F() {
  //   {
  //     var x : 32;
  //   }
  // }
  auto* stmt = Decl(Var("x", ty.i32()));
  auto* block = Block(stmt);
  auto* f = Func("F", {}, ty.void_(), {block});

  ASSERT_TRUE(r()->Resolve()) << r()->error();

  {
    auto* s = Sem().Get(block);
    ASSERT_NE(s, nullptr);
    EXPECT_TRUE(s->Is<sem::BlockStatement>());
    EXPECT_EQ(s, s->Block());
    EXPECT_EQ(s->Parent(), s->FindFirstParent<sem::FunctionBlockStatement>());
  }
  {
    auto* s = Sem().Get(stmt);
    ASSERT_NE(s, nullptr);
    ASSERT_NE(s->Block(), nullptr);
    EXPECT_EQ(s->Block(), s->FindFirstParent<sem::BlockStatement>());
    EXPECT_EQ(s->Block()->Parent(),
              s->FindFirstParent<sem::FunctionBlockStatement>());
    ASSERT_TRUE(s->Block()->Parent()->Is<sem::FunctionBlockStatement>());
    EXPECT_EQ(s->Function()->Declaration(), f);
    EXPECT_EQ(s->Block()->Parent()->Parent(), nullptr);
  }
}

TEST_F(ResolverCompoundStatementTest, Loop) {
  // fn F() {
  //   loop {
  //     stmt_a;
  //     continuing {
  //       stmt_b;
  //     }
  //   }
  // }
  auto* stmt_a = Ignore(1);
  auto* stmt_b = Ignore(1);
  auto* loop = Loop(Block(stmt_a), Block(stmt_b));
  auto* f = Func("F", {}, ty.void_(), {loop});

  ASSERT_TRUE(r()->Resolve()) << r()->error();

  {
    auto* s = Sem().Get(loop);
    ASSERT_NE(s, nullptr);
    EXPECT_TRUE(s->Is<sem::LoopStatement>());
    EXPECT_EQ(s->Parent(), s->FindFirstParent<sem::FunctionBlockStatement>());
    EXPECT_EQ(s->Parent(), s->Block());
  }
  {
    auto* s = Sem().Get(stmt_a);
    ASSERT_NE(s, nullptr);
    ASSERT_NE(s->Block(), nullptr);
    EXPECT_EQ(s->Parent(), s->Block());
    EXPECT_EQ(s->Parent(), s->FindFirstParent<sem::LoopBlockStatement>());

    EXPECT_EQ(s->Parent()->Parent(), s->FindFirstParent<sem::LoopStatement>());
    EXPECT_TRUE(Is<sem::LoopStatement>(s->Parent()->Parent()));

    EXPECT_EQ(s->Parent()->Parent()->Parent(),
              s->FindFirstParent<sem::FunctionBlockStatement>());
    EXPECT_TRUE(
        Is<sem::FunctionBlockStatement>(s->Parent()->Parent()->Parent()));

    EXPECT_EQ(s->Function()->Declaration(), f);

    EXPECT_EQ(s->Parent()->Parent()->Parent()->Parent(), nullptr);
  }
  {
    auto* s = Sem().Get(stmt_b);
    ASSERT_NE(s, nullptr);
    ASSERT_NE(s->Block(), nullptr);
    EXPECT_EQ(s->Parent(), s->Block());

    EXPECT_EQ(s->Parent(),
              s->FindFirstParent<sem::LoopContinuingBlockStatement>());
    EXPECT_TRUE(Is<sem::LoopContinuingBlockStatement>(s->Parent()));

    EXPECT_EQ(s->Parent()->Parent(),
              s->FindFirstParent<sem::LoopBlockStatement>());
    EXPECT_TRUE(Is<sem::LoopBlockStatement>(s->Parent()->Parent()));

    EXPECT_EQ(s->Parent()->Parent()->Parent(),
              s->FindFirstParent<sem::LoopStatement>());
    EXPECT_TRUE(Is<sem::LoopStatement>(s->Parent()->Parent()->Parent()));

    EXPECT_EQ(s->Parent()->Parent()->Parent()->Parent(),
              s->FindFirstParent<sem::FunctionBlockStatement>());
    EXPECT_TRUE(Is<sem::FunctionBlockStatement>(
        s->Parent()->Parent()->Parent()->Parent()));
    EXPECT_EQ(s->Function()->Declaration(), f);

    EXPECT_EQ(s->Parent()->Parent()->Parent()->Parent()->Parent(), nullptr);
  }
}

TEST_F(ResolverCompoundStatementTest, ForLoop) {
  // fn F() {
  //   for (var i : u32; true; i = i + 1u) {
  //     return;
  //   }
  // }
  auto* init = Decl(Var("i", ty.u32()));
  auto* cond = Expr(true);
  auto* cont = Assign("i", Add("i", 1u));
  auto* stmt = Return();
  auto* body = Block(stmt);
  auto* for_ = For(init, cond, cont, body);
  auto* f = Func("F", {}, ty.void_(), {for_});

  ASSERT_TRUE(r()->Resolve()) << r()->error();

  {
    auto* s = Sem().Get(for_);
    ASSERT_NE(s, nullptr);
    EXPECT_TRUE(s->Is<sem::ForLoopStatement>());
    EXPECT_EQ(s->Parent(), s->FindFirstParent<sem::FunctionBlockStatement>());
    EXPECT_EQ(s->Parent(), s->Block());
  }
  {
    auto* s = Sem().Get(init);
    ASSERT_NE(s, nullptr);
    EXPECT_EQ(s->Parent(), s->FindFirstParent<sem::ForLoopStatement>());
    EXPECT_TRUE(Is<sem::ForLoopStatement>(s->Parent()));
    EXPECT_EQ(s->Block(), s->FindFirstParent<sem::FunctionBlockStatement>());
    EXPECT_TRUE(Is<sem::FunctionBlockStatement>(s->Parent()->Parent()));
  }
  {  // Condition expression's statement is the for-loop itself
    auto* e = Sem().Get(cond);
    ASSERT_NE(e, nullptr);
    auto* s = e->Stmt();
    ASSERT_NE(s, nullptr);
    ASSERT_TRUE(Is<sem::ForLoopStatement>(s));
    ASSERT_NE(s->Parent(), nullptr);
    EXPECT_EQ(s->Parent(), s->Block());
    EXPECT_EQ(s->Parent(), s->FindFirstParent<sem::FunctionBlockStatement>());
    EXPECT_TRUE(Is<sem::FunctionBlockStatement>(s->Block()));
  }
  {
    auto* s = Sem().Get(cont);
    ASSERT_NE(s, nullptr);
    EXPECT_EQ(s->Parent(), s->FindFirstParent<sem::ForLoopStatement>());
    EXPECT_TRUE(Is<sem::ForLoopStatement>(s->Parent()));
    EXPECT_EQ(s->Block(), s->FindFirstParent<sem::FunctionBlockStatement>());
    EXPECT_TRUE(Is<sem::FunctionBlockStatement>(s->Parent()->Parent()));
  }
  {
    auto* s = Sem().Get(stmt);
    ASSERT_NE(s, nullptr);
    ASSERT_NE(s->Block(), nullptr);
    EXPECT_EQ(s->Parent(), s->Block());
    EXPECT_EQ(s->Block(), s->FindFirstParent<sem::LoopBlockStatement>());
    EXPECT_TRUE(Is<sem::ForLoopStatement>(s->Parent()->Parent()));
    EXPECT_EQ(s->Block()->Parent(),
              s->FindFirstParent<sem::ForLoopStatement>());
    ASSERT_TRUE(
        Is<sem::FunctionBlockStatement>(s->Block()->Parent()->Parent()));
    EXPECT_EQ(s->Block()->Parent()->Parent(),
              s->FindFirstParent<sem::FunctionBlockStatement>());
    EXPECT_EQ(s->Function()->Declaration(), f);
    EXPECT_EQ(s->Block()->Parent()->Parent()->Parent(), nullptr);
  }
}

TEST_F(ResolverCompoundStatementTest, If) {
  // fn F() {
  //   if (cond_a) {
  //     stat_a;
  //   } elseif (cond_b) {
  //     stat_b;
  //   } else {
  //     stat_c;
  //   }
  // }

  auto* cond_a = Expr(true);
  auto* stmt_a = Ignore(1);
  auto* cond_b = Expr(true);
  auto* stmt_b = Ignore(1);
  auto* stmt_c = Ignore(1);
  auto* if_stmt = If(cond_a, Block(stmt_a), Else(cond_b, Block(stmt_b)),
                     Else(nullptr, Block(stmt_c)));
  WrapInFunction(if_stmt);

  ASSERT_TRUE(r()->Resolve()) << r()->error();

  {
    auto* s = Sem().Get(if_stmt);
    ASSERT_NE(s, nullptr);
    EXPECT_TRUE(s->Is<sem::IfStatement>());
    EXPECT_EQ(s->Parent(), s->FindFirstParent<sem::FunctionBlockStatement>());
    EXPECT_EQ(s->Parent(), s->Block());
  }
  {
    auto* e = Sem().Get(cond_a);
    ASSERT_NE(e, nullptr);
    auto* s = e->Stmt();
    ASSERT_NE(s, nullptr);
    EXPECT_TRUE(s->Is<sem::IfStatement>());
    EXPECT_EQ(s->Parent(), s->FindFirstParent<sem::FunctionBlockStatement>());
    EXPECT_EQ(s->Parent(), s->Block());
  }
  {
    auto* s = Sem().Get(stmt_a);
    ASSERT_NE(s, nullptr);
    EXPECT_EQ(s->Parent(), s->FindFirstParent<sem::BlockStatement>());
    EXPECT_EQ(s->Parent(), s->Block());
    EXPECT_EQ(s->Parent()->Parent(), s->FindFirstParent<sem::IfStatement>());
    EXPECT_EQ(s->Parent()->Parent()->Parent(),
              s->FindFirstParent<sem::FunctionBlockStatement>());
  }
  {
    auto* e = Sem().Get(cond_b);
    ASSERT_NE(e, nullptr);
    auto* s = e->Stmt();
    ASSERT_NE(s, nullptr);
    EXPECT_TRUE(s->Is<sem::ElseStatement>());
    EXPECT_EQ(s->Parent(), s->FindFirstParent<sem::IfStatement>());
    EXPECT_EQ(s->Parent()->Parent(),
              s->FindFirstParent<sem::FunctionBlockStatement>());
    EXPECT_EQ(s->Parent()->Parent(), s->Block());
  }
  {
    auto* s = Sem().Get(stmt_b);
    ASSERT_NE(s, nullptr);
    EXPECT_EQ(s->Parent(), s->FindFirstParent<sem::BlockStatement>());
    EXPECT_EQ(s->Parent(), s->Block());
    EXPECT_EQ(s->Parent()->Parent(), s->FindFirstParent<sem::ElseStatement>());
    EXPECT_EQ(s->Parent()->Parent()->Parent(),
              s->FindFirstParent<sem::IfStatement>());
    EXPECT_EQ(s->Parent()->Parent()->Parent()->Parent(),
              s->FindFirstParent<sem::FunctionBlockStatement>());
  }
  {
    auto* s = Sem().Get(stmt_c);
    ASSERT_NE(s, nullptr);
    EXPECT_EQ(s->Parent(), s->FindFirstParent<sem::BlockStatement>());
    EXPECT_EQ(s->Parent(), s->Block());
    EXPECT_EQ(s->Parent()->Parent(), s->FindFirstParent<sem::ElseStatement>());
    EXPECT_EQ(s->Parent()->Parent()->Parent(),
              s->FindFirstParent<sem::IfStatement>());
    EXPECT_EQ(s->Parent()->Parent()->Parent()->Parent(),
              s->FindFirstParent<sem::FunctionBlockStatement>());
  }
}

TEST_F(ResolverCompoundStatementTest, Switch) {
  // fn F() {
  //   switch (expr) {
  //     case 1: {
  //        stmt_a;
  //     }
  //     case 2: {
  //        stmt_b;
  //     }
  //     default: {
  //        stmt_c;
  //     }
  //   }
  // }

  auto* expr = Expr(5);
  auto* stmt_a = Ignore(1);
  auto* stmt_b = Ignore(1);
  auto* stmt_c = Ignore(1);
  auto* swi = Switch(expr, Case(Expr(1), Block(stmt_a)),
                     Case(Expr(2), Block(stmt_b)), DefaultCase(Block(stmt_c)));
  WrapInFunction(swi);

  ASSERT_TRUE(r()->Resolve()) << r()->error();

  {
    auto* s = Sem().Get(swi);
    ASSERT_NE(s, nullptr);
    EXPECT_TRUE(s->Is<sem::SwitchStatement>());
    EXPECT_EQ(s->Parent(), s->FindFirstParent<sem::FunctionBlockStatement>());
    EXPECT_EQ(s->Parent(), s->Block());
  }
  {
    auto* e = Sem().Get(expr);
    ASSERT_NE(e, nullptr);
    auto* s = e->Stmt();
    ASSERT_NE(s, nullptr);
    EXPECT_TRUE(s->Is<sem::SwitchStatement>());
    EXPECT_EQ(s->Parent(), s->FindFirstParent<sem::FunctionBlockStatement>());
    EXPECT_EQ(s->Parent(), s->Block());
  }
  {
    auto* s = Sem().Get(stmt_a);
    ASSERT_NE(s, nullptr);
    EXPECT_EQ(s->Parent(), s->FindFirstParent<sem::SwitchCaseBlockStatement>());
    EXPECT_EQ(s->Parent(), s->Block());
    EXPECT_EQ(s->Parent()->Parent(),
              s->FindFirstParent<sem::SwitchStatement>());
    EXPECT_EQ(s->Parent()->Parent()->Parent(),
              s->FindFirstParent<sem::FunctionBlockStatement>());
  }
  {
    auto* s = Sem().Get(stmt_b);
    ASSERT_NE(s, nullptr);
    EXPECT_EQ(s->Parent(), s->FindFirstParent<sem::SwitchCaseBlockStatement>());
    EXPECT_EQ(s->Parent(), s->Block());
    EXPECT_EQ(s->Parent()->Parent(),
              s->FindFirstParent<sem::SwitchStatement>());
    EXPECT_EQ(s->Parent()->Parent()->Parent(),
              s->FindFirstParent<sem::FunctionBlockStatement>());
  }
  {
    auto* s = Sem().Get(stmt_c);
    ASSERT_NE(s, nullptr);
    EXPECT_EQ(s->Parent(), s->FindFirstParent<sem::SwitchCaseBlockStatement>());
    EXPECT_EQ(s->Parent(), s->Block());
    EXPECT_EQ(s->Parent()->Parent(),
              s->FindFirstParent<sem::SwitchStatement>());
    EXPECT_EQ(s->Parent()->Parent()->Parent(),
              s->FindFirstParent<sem::FunctionBlockStatement>());
  }
}

}  // namespace
}  // namespace resolver
}  // namespace tint
