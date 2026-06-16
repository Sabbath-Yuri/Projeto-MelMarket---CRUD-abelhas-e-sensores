# MelMarket

**Trabalho:** Sistema CRUD de abelhas e sensores.

---

## Descrição

Sistema de cadastro e monitoramento de abelhas sem ferrão e sensores ambientais associados. Permite gerenciar espécies de abelhas por região, vincular sensores de temperatura, luminosidade e umidade a cada abelha, e gerar relatórios de produção, estoque e faturamento de mel.

---

## Objetivos
Desenvolver um sistema CRUD em linguagem C para gerenciamento de abelhas sem ferrão e sensores ambientais, aplicando conceitos de estruturas de dados, modularização e manipulação de registros.

---

## Compilação

```
gcc MelMarket.c -o MelMarket
```

## Execução

```
./MelMarket
```

> **Atenção:** o sistema foi desenvolvido para Windows. Em Linux/Mac, remova o `#include <windows.h>` e as chamadas `SetConsoleOutputCP` e `SetConsoleCP` do código.

---
## Conceitos Aplicados

- Structs
- Ponteiros
- Alocação dinâmica de memória
- Listas encadeadas
- Relacionamento entre entidades
- CRUD completo

---
## Exemplo de Uso

1. Cadastrar uma abelha
2. Associar sensores
3. Registrar leituras
4. Gerar relatórios de produção e faturamento

---
## Funcionalidades

- Cadastro, listagem, busca, alteração e remoção de abelhas e sensores
- Gerenciamento de sensores vinculados às abelhas (temperatura, luminosidade e umidade)
- Remoção automática de sensores ao excluir uma abelha
- Relatórios de média de produção de mel, média de temperatura, distribuição por região, estoque e faturamento

---

## Bugs conhecidos

- Não há persistência em arquivo; os dados se perdem ao encerrar o programa.
