(TeX-add-style-hook "uebertr01"
 (lambda ()
    (LaTeX-add-environments
     "satz"
     "defi"
     "lemma")
    (LaTeX-add-labels
     "eq:1"
     "eq:2"
     "eq:3"
     "eq:4"
     "eq:5"
     "eq:6"
     "eq:7"
     "eq:8"
     "fig:delta"
     "eq:9"
     "eq:10"
     "fig:vgl1"
     "fig:vgl2"
     "fig:uebertr"
     "eq:11")
    (TeX-add-symbols
     '("abs" 0)
     '("skp" 2)
     '("Ve" 1)
     '("Ten" 1)
     '("Mat" 1)
     "diff"
     "dx"
     "dvx"
     "e"
     "E"
     "ir"
     "I"
     "R"
     "folgt"
     "gdw"
     "const"
     "NAME"
     "FACH"
     "TITEL"
     "DATUM")
    (TeX-run-style-hooks
     "hyperref"
     "fancyhdr"
     "multicol"
     "graphicx"
     "subfigure"
     "enumerate"
     "latexsym"
     "amsthm"
     "amssymb"
     "amsmath"
     "fontenc"
     "T1"
     "inputenc"
     "utf8"
     "babel"
     "ngerman"
     "latex2e"
     "art12"
     "article"
     "a4paper"
     "12pt")))

