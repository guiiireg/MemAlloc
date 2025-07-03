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
├── src/                    # Code source principal
│   ├── mem_core.c         # Fonctions d'allocation principales
│   ├── mem_utils.c        # Utilitaires et gestion des blocs
│   └── mem_debug.c        # Debugging et statistiques
├── include/               # Fichiers d'en-tête
│   ├── mem_alloc.h        # Interface publique
│   └── mem_utils.h        # Interface interne
├── tests/                 # Tests unitaires (Criterion)
│   └── test_mem_alloc.c   # Suite de tests complète
├── examples/              # Exemples d'utilisation
│   ├── basic_example.c    # Utilisation basique
│   └── advanced_example.c # Fonctionnalités avancées
├── lib/                   # Bibliothèques compilées
├── build/                 # Fichiers de build
└── Makefile              # Système de build complet
```

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

- **Gestion mémoire bas niveau** : Implémentation complète d'allocateur
- **Structures de données** : Listes chaînées, gestion de blocs
- **Pointeurs et arithmétique** : Manipulation avancée de pointeurs
- **Debugging système** : Outils de diagnostic et validation
- **Tests unitaires** : Suite de tests complète avec Criterion
- **Build system** : Makefile avancé avec multiples configurations
- **Optimisation** : Algorithmes efficaces et mesures de performance

---

**Auteur** : Gestionnaire de Mémoire Personnalisé  
**Version** : 1.0.0  
**Date** : 2025
