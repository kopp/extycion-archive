

index.adoc: Readme.md
	pandoc --standalone $< -o $@
	sed -i '1s,==,=,' $@
	sed -i 1a\ ":toc:\n:sectnums:\n" $@

index.html: index.adoc
	asciidoctor $<
