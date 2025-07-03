# Custom Memory Allocator - MemAlloc

[![Build Status](https://img.shields.io/badge/build-passing-brightgreen)]()
[![License](https://img.shields.io/badge/license-MIT-blue)]()
[![Version](https://img.shields.io/badge/version-1.0.0-blue)]()
[![Maintainer](https://img.shields.io/badge/maintainer-@guiiireg-purple)](https://github.com/guiiireg)

Un gestionnaire de mémoire personnalisé implémenté en C pur, offrant des fonctionnalités avancées de gestion mémoire, détection de fuites, et analyse de fragmentation.

---

## 📋 Navigation Rapide

- [🎯 Objectifs du Projet](#-objectifs-du-projet)
- [🏗️ Architecture](#️-architecture)
- [🚀 Installation Rapide](#-installation-rapide)
- [🎮 Utilisation](#-utilisation)
- [🧪 Tests et Validation](#-tests-et-validation)
- [📊 Fonctionnalités Techniques](#-fonctionnalités-techniques)
- [🤝 Contribution](#-contribution)
- [📚 Documentation Complète](#-documentation-complète)

---

## 🎯 Objectifs du Projet

Ce projet implémente un gestionnaire de mémoire complet avec :

- **Allocation personnalisée** : Implémentation de `malloc()` et `free()` 
- **Gestion des fuites** : Détection et rapport des fuites mémoire
- **Défragmentation** : Algorithmes de réduction de la fragmentation
- **Analyse statistique** : Collecte détaillée de métriques d'utilisation
- **Debug avancé** : Outils de validation et de diagnostic

## 🏗️ Architecture

```
MemAlloc/
├── src/                        # Code source principal
│   ├── mem_core/              # 🔧 Fonctions d'allocation principales
│   │   ├── mem_malloc.c       #   - Allocation de mémoire
│   │   ├── mem_calloc.c       #   - Allocation initialisée à zéro  
│   │   ├── mem_realloc.c      #   - Réallocation de blocs
│   │   ├── mem_free.c         #   - Libération de mémoire
│   │   ├── mem_init.c         #   - Initialisation et nettoyage
│   │   └── mem_globals.c      #   - Variables globales et utilitaires
│   ├── mem_debug/             # 🐛 Debugging et diagnostics
│   │   ├── mem_stats.c        #   - Collecte et affichage des statistiques
│   │   ├── mem_heap_display.c #   - Visualisation du layout du heap
│   │   ├── mem_integrity.c    #   - Validation de l'intégrité
│   │   ├── mem_leak_detection.c #  - Détection de fuites mémoire
│   │   └── mem_debug_utils.c  #   - Utilitaires debug et défragmentation
│   ├── mem_utils/             # ⚙️ Utilitaires et gestion des blocs
│   │   ├── mem_alignment.c    #   - Alignement mémoire et recherche
│   │   ├── mem_splitting.c    #   - Division des blocs
│   │   ├── mem_merging.c      #   - Fusion des blocs adjacents
│   │   └── mem_validation.c   #   - Validation et conversion de pointeurs
│   ├── mem_core.c             # Interface principale du module core
│   ├── mem_debug.c            # Interface principale du module debug
│   └── mem_utils.c            # Interface principale du module utils
├── include/                   # Fichiers d'en-tête
│   ├── mem_alloc.h           # Interface publique
│   └── mem_utils.h           # Interface interne
├── tests/                    # Tests unitaires (Criterion)
│   └── test_mem_alloc.c      # Suite de tests complète
├── examples/                 # Exemples d'utilisation
│   ├── basic_example.c       # Utilisation basique
│   ├── advanced_example.c    # Fonctionnalités avancées
│   └── project_showcase.c    # Démonstration complète
├── lib/                      # Bibliothèques compilées
├── build/                    # Fichiers de build
└── Makefile                 # Système de build complet
```

### 🎯 Organisation Modulaire

Le projet utilise une **architecture modulaire** avec des fonctions courtes (≤ 20 lignes) réparties en modules spécialisés :

#### **📁 Module Core (`mem_core/`)**
Fonctions essentielles d'allocation mémoire :
- **Allocation** : `mem_malloc()`, `mem_calloc()`, `mem_realloc()`
- **Libération** : `mem_free()` avec validation et fusion
- **Initialisation** : `mem_init()` et `mem_cleanup()` pour la gestion du heap
- **État global** : Variables partagées et utilitaires de base

#### **📁 Module Debug (`mem_debug/`)**  
Outils de diagnostic et analyse :
- **Statistiques** : Collecte et affichage des métriques d'utilisation
- **Visualisation** : Affichage détaillé du layout mémoire
- **Intégrité** : Validation de la cohérence du heap
- **Fuites** : Détection et rapport des blocs non libérés
- **Défragmentation** : Algorithmes de fusion des blocs libres

#### **📁 Module Utils (`mem_utils/`)**
Utilitaires de gestion des blocs :
- **Alignement** : Calculs d'alignement et recherche de blocs libres
- **Division** : Séparation des blocs en portions plus petites
- **Fusion** : Combinaison des blocs adjacents libres
- **Validation** : Vérification des pointeurs et conversion bloc/pointeur

## 🚀 Installation Rapide

### Méthode Automatique (Recommandée)
```bash
git clone https://github.com/guiiireg/MemAlloc.git
cd MemAlloc
./install.sh
```

### Méthode Manuelle
```bash
# Installation des dépendances
sudo apt-get install build-essential libcriterion-dev valgrind

# Compilation
make build

# Tests
make test

# Exemples
make run-basic
```

> 📖 **Guide détaillé** : Voir [Installation Complète](#-compilation-et-installation) plus bas

## 🎮 Utilisation

### Utilisation Basique

```c
#include "mem_alloc.h"

int main() {
    // Initialisation du gestionnaire
    mem_init(1024 * 1024);  // 1MB de heap
    
    // Allocation
    void *ptr = mem_malloc(100);
    
    // Utilisation...
    strcpy((char*)ptr, "Hello World");
    
    // Libération
    mem_free(ptr);
    
    // Nettoyage
    mem_cleanup();
    return 0;
}
```

### Fonctionnalités Avancées

```c
// Statistiques détaillées
mem_print_stats();

// Détection de fuites
mem_detect_leaks();

// Vérification d'intégrité
if (!mem_check_integrity()) {
    printf("Corruption détectée!\n");
}

// Défragmentation
mem_defragment();

// Affichage du layout mémoire
mem_print_heap();
```

## 🧪 Tests et Validation

### Exécution des Tests

```bash
# Tests unitaires complets
make test

# Tests avec sortie verbose
make test-verbose

# Tests sous Valgrind
make valgrind-test

# Rapport de couverture
make test-coverage
```

### Exemples d'Exécution

```bash
# Exemple basique
make run-basic

# Exemple avancé avec stress test
make run-advanced

# Debug avec GDB
make gdb-test
```

## 📊 Fonctionnalités Techniques

### 🏗️ Conception Modulaire

Le projet suit une **architecture en modules** avec une séparation claire des responsabilités :

- **Fonctions courtes** : Toutes les fonctions ≤ 20 lignes pour une lisibilité optimale
- **Modules spécialisés** : Chaque module a une responsabilité unique et bien définie  
- **Encapsulation** : Interfaces claires entre les modules via les headers
- **Maintenabilité** : Structure facilitant les modifications et extensions

### Algorithmes Implémentés

- **First-fit allocation** : Recherche du premier bloc libre suffisant
- **Block splitting** : Division des blocs pour optimiser l'utilisation
- **Block merging** : Fusion des blocs adjacents libres
- **Alignment enforcement** : Alignement mémoire pour performance optimale

### Structures de Données

```c
typedef struct mem_block {
    size_t size;              // Taille du bloc
    bool is_free;             // État du bloc
    uint32_t magic;           // Nombre magique pour validation
    struct mem_block *next;   // Bloc suivant
    struct mem_block *prev;   // Bloc précédent
} mem_block_t;
```

### Statistiques Collectées

- Mémoire totale allouée/libérée
- Utilisation courante et pic d'utilisation
- Nombre d'allocations/libérations
- Ratio de fragmentation
- Nombre de blocs actifs

### 🔧 Organisation des Fonctions par Module

#### **Core Functions** (`mem_core/`)
```c
// Allocation principale - fonctions helper pour stats et préparation
void* mem_malloc(size_t size);
static void update_allocation_stats();
static mem_block_t* prepare_block();

// Réallocation - fonctions helper pour différents cas
void* mem_realloc(void *ptr, size_t new_size);
static void* handle_size_decrease();
static void* handle_size_increase();

// Initialisation - fonctions helper pour setup
int mem_init(size_t heap_size);
static int setup_heap();
static void initialize_first_block();
```

#### **Debug Functions** (`mem_debug/`)
```c
// Statistiques - calcul des métriques
void mem_get_stats(mem_stats_t *stats);
static void calculate_heap_metrics();

// Affichage heap - fonctions helper pour formatage
void mem_print_heap(void);
static void print_heap_header();
static void print_block_info();

// Intégrité - validation modulaire
bool mem_check_integrity(void);
static bool validate_block();
```

#### **Utility Functions** (`mem_utils/`)
```c
// Division de blocs - helper pour setup
mem_block_t* mem_split_block();
static void setup_new_block();

// Fusion de blocs - opérations directionnelles
void mem_merge_blocks(mem_block_t *block);
static void merge_with_next();
static void merge_with_prev();

// Validation - vérifications spécialisées
bool mem_is_valid_ptr(void *ptr);
static bool is_ptr_in_heap_bounds();
static bool is_block_valid();
```

### 💡 Avantages de l'Architecture Modulaire

- **🔍 Lisibilité** : Code plus clair avec des fonctions courtes et focalisées
- **🛠️ Maintenabilité** : Modifications isolées dans des modules spécifiques
- **🧪 Testabilité** : Tests ciblés par module et fonction
- **📈 Évolutivité** : Ajout facile de nouvelles fonctionnalités
- **🎯 Spécialisation** : Chaque fichier a une responsabilité unique
- **🔧 Debug facilité** : Localisation rapide des problèmes par module

## 🔧 Outils de Développement

### Analyse Statique

```bash
# Analyse avec Cppcheck
make analyze

# Linting du code
make lint

# Formatage automatique
make format
```

### Profiling et Benchmarks

```bash
# Build avec profiling
make CONFIG=profile examples

# Benchmark de performance
make benchmark

# Comparaison avec malloc système
make run-advanced
```

### Debugging Avancé

```bash
# Build debug avec sanitizers
make CONFIG=debug build

# Tests mémoire avec Valgrind
make valgrind-examples

# Debug interactif
make gdb-test
```

## 📈 Métriques de Performance

Le gestionnaire fournit des métriques détaillées :

- **Temps d'allocation** : Mesure de la latence
- **Fragmentation** : Pourcentage de mémoire fragmentée
- **Efficacité** : Ratio mémoire utile/overhead
- **Fuites** : Détection automatique des fuites

## 🛡️ Sécurité et Validation

### Protections Implémentées

- **Magic numbers** : Détection de corruption
- **Boundary checking** : Vérification des limites
- **Double-free protection** : Prévention des libérations multiples
- **Invalid pointer detection** : Validation des pointeurs

### Outils de Debug

- Mode debug avec informations détaillées
- Tracking des allocations avec fichier/ligne
- Validation d'intégrité du heap
- Rapports de fuites mémoire

## 📚 Documentation

### Génération de la Documentation

```bash
# Documentation Doxygen
make docs

# Pages de manuel
make man
```

### Structure des Headers

- `mem_alloc.h` : Interface publique complète
- `mem_utils.h` : Fonctions internes (non exposées)

---

## 📚 Documentation Complète

### 📋 Guides et Références
- **[CHANGELOG.md](CHANGELOG.md)** - Historique des versions et nouveautés
- **[LICENSE](LICENSE)** - Licence MIT du projet
- **[PROJECT_SUMMARY.md](PROJECT_SUMMARY.md)** - Résumé technique complet du projet

### 🛠️ Développement et Contribution
- **[CONTRIBUTING.md](.github/CONTRIBUTING.md)** - Guide pour les rapports de bugs et demandes d'améliorations
- **[Issue Templates](.github/ISSUE_TEMPLATE/)** - Templates pour rapporter des problèmes
- **[Workflows GitHub](.github/workflows/)** - CI/CD automatisé

### 💡 Exemples Pratiques
- **[examples/basic_example.c](examples/basic_example.c)** - Utilisation basique du gestionnaire
- **[examples/advanced_example.c](examples/advanced_example.c)** - Fonctionnalités avancées et benchmarks
- **[examples/project_showcase.c](examples/project_showcase.c)** - Démonstration complète des capacités

### 🧪 Tests et Validation
- **[tests/test_mem_alloc.c](tests/test_mem_alloc.c)** - Suite de tests unitaires complète
- **[Makefile](Makefile)** - Système de build avec 30+ commandes

---

## 🚀 Compilation et Installation

### Prérequis

- GCC (C99 ou plus récent)
- Make
- Criterion (pour les tests unitaires)
- Valgrind (optionnel, pour le debugging)

### Installation de Criterion

```bash
# Ubuntu/Debian
sudo apt-get install libcriterion-dev

# Arch Linux
sudo pacman -S criterion

# macOS (avec Homebrew)
brew install criterion
```

### Compilation Détaillée

```bash
# Afficher l'aide complète
make help

# Compilation debug (par défaut)
make build

# Compilation release optimisée
make CONFIG=release static

# Compilation avec toutes les bibliothèques
make all-libs

# Installation système
sudo make install
```
## 🤝 Contribution

**Note importante** : Ce projet ne accepte pas de contributions directes de code. 

### Comment aider
- 🐛 **Rapports de bugs** : Utilisez les [GitHub Issues](https://github.com/guiiireg/MemAlloc/issues) avec le template approprié
- 💡 **Demandes d'améliorations** : Proposez des nouvelles fonctionnalités via les issues
- 🗣️ **Feedback** : Partagez votre expérience d'utilisation et suggestions
- 📊 **Tests** : Reportez des résultats de performance ou des cas d'usage

### Maintenance
Ce projet est maintenu par [@guiiireg](https://github.com/guiiireg). Tous les correctifs de bugs et implémentations de nouvelles fonctionnalités sont gérés par le mainteneur pour assurer la cohérence et la qualité du code.

Pour plus de détails, consultez [CONTRIBUTING.md](.github/CONTRIBUTING.md).

---

## 📝 Licence

Ce projet est sous licence MIT. Voir le fichier LICENSE pour plus de détails.

## 🏆 Compétences Démontrées

- **🏗️ Architecture modulaire** : Conception en modules spécialisés avec responsabilités claires
- **📏 Code quality** : Fonctions courtes (≤20 lignes) pour une lisibilité optimale
- **🔧 Gestion mémoire bas niveau** : Implémentation complète d'allocateur personnalisé
- **🔗 Structures de données** : Listes chaînées bidirectionnelles et gestion avancée de blocs
- **🎯 Pointeurs et arithmétique** : Manipulation experte de pointeurs et calculs d'adresses
- **🐛 Debugging système** : Outils complets de diagnostic, validation et détection de fuites
- **✅ Tests unitaires** : Suite de tests exhaustive avec framework Criterion
- **⚙️ Build system** : Makefile avancé avec 30+ commandes et configurations multiples
- **🚀 Optimisation** : Algorithmes efficaces avec mesures et analyse de performance
- **📁 Organisation du code** : Séparation modulaire claire entre core, debug et utilities
- **🛡️ Sécurité** : Validation robuste avec magic numbers et protection contre la corruption

---

**Auteur** : Gestionnaire de Mémoire Personnalisé  
**Version** : 1.0.0  
**Date** : 2025
