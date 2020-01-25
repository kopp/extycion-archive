<html>
  <head>
    <title>Physiker-Blog: Files</title>
    <meta name=Author content="Michael Kopp">
		<link rel=stylesheet tpye=text/css href=style.css>
    <style></style>
  </head>
  <body>




<div id=navi>
<?php
include("navi.incl");
?>
</div>




<div id=inhalt>


<h1 id=seitentitel>Files -- Download</h1>



<h3>Wichtiges (shortcut zu manchen Sachen)</h3>

<p>Folgende Dateien hab ich als so wichtig angesehen, dass ich ihnen hier noch extra Platz widme:
<ul>
<li>Script zu Experimentalphysik I und II (Mechanik, E-Lehre), Bechinger, WS09, SS10: <a href=./files/exphys/exphys1_script01.pdf>pdf</a> oder <a href=./files/exphys/exphys1_script01.ps>ps</a></li>
<li>Meine Mitschriebe zur Vorlesung <i>Weiche und biologische Materie</i> bei Prof. Bechinger, WS 2010 und SS 2011:
<a href=./files/weich/aufschrieb_bearbeitet.pdf>pdf</a>.
<li>Unsere (Dreamteam zusammen mit Paul Menczel) Praktikumsprotokolle.
Sie liegen alle auf svn-Servern von <a href=xp-dev.com>xp-dev.com</a>:
    <ul>
    <li>Elektronikpraktikum: <a href=http://xp-dev.com/svn/ep-repo/>http://xp-dev.com/svn/ep-repo/</a></li>
    <li>Physikalisches Praktikum II: <a href=http://xp-dev.com/svn/prakt2/>http://xp-dev.com/svn/prakt2/</a></li>
    <li>Physikalisches Fortgeschrittenenpraktikum: <a href=http://xp-dev.com/svn/fprakt/>http://xp-dev.com/svn/fprakt/</a></li>
    </ul>
Und man kann sie, wenn man ein SVN (Subversion) Tool hat (Mac/Linux: <i>subversion</i>, Windows <i>TortoiseSVN</i> (laut Paul)), einfach per
<pre>$ svn checkout http://xp-dev.com/svn/fprakt/</pre>
runterladen. Hat man <i>Gnu Make</i> (und nat&uuml;rlich LaTeX) installiert, lassen sich die Protokolle meist in <i>abgabe</i> mit
<pre>$ make pdf</pre>
bauen.
</ul>
</p>





<h3>Organisation von allem Anderen</h3>



<p>Neues System: &Uuml;ber die Links weiter unten kommt man direkt zu den hier lagernden Dateien. Man kann sich durch die Ordner navigieren und die einzelnen Dateien schnell und elegant ausw&auml;hlen.<p>

<p>Unten auf den Seiten steht das letzte Aktualisierungsdatum der Ordnerstruktur und hinter jeder Datei das Datum der letzten &auml;nderung -- so kann man leicht sehen, ob eine Datei neu ist oder nicht.</p>

<p>Unter der Liste von Dateien und Ordnern k&ouml;nnen noch zus&auml;tzlich Kommentare sein oder zu den einzelnen Dateien direkt darunter mit der Endung ''.about'' (also bspw. bezieht sich <tt>foo.about</tt> auf <tt>foo</tt>).</p>


<p>Die Ordnung ist einfach: 
<ul>
<li>Die K&uuml;rzel beziehen sich auf das jeweilige Fach und in dem Ordner des Faches sind Unterordner f&uuml;r Vorlesungen/&Uuml;bungen. </li>
<li>Die Nummer bezieht sich auf das Semester. (<tt>ueb2</tt> sind die &Uuml;bungen aus dem 2. Semester. <tt>vorl</tt> oder <tt>vorl1</tt> enth&auml;lt Vorlesungsmitschriebe des 1. Semesters.)</li>
<li>Die Unterkategorien sind:
	<ul>
	<li>ueb: &Uuml;bungen</li>
	<li>vorl: Vorlesungsmitschriebe und eigene Texte</li>
	<li>my: Eigene Texte</li>
	</ul>
</ul>

<h3>Zu den einzelnen Vorlesungen</h3>



<p><b>Alles findet man <a href=./files>hier</a>!</b></p>

<p align=center><b><a href=./files>HIER KLICKEN</a></b></p>


<p>Weil es manche User nicht geschafft haben, den <i>uebergeordneter Ordner</i>-Button zu verwenden, muss ich leider drastischere Schritte einleiten ...</p>

<p>Ab jetzt ist nur noch der Link oben da; alle F&auml;cher sind darunter aber verlinkt!</p>



<!--
<ul>
<li>Allgemeines &uuml;ber das Studium: <a href=./files/allg>allg</a></li>
<li>Allgemeine und Anorganische Chemie I, Gudat, WS08: <a href=./files/aach>aach</a></li>
<li>Analysis I - II, Weidl, WS09, SS10  <br>Analysis III, Br&uuml;dern, WS10: <a href=./files/ana>ana</a></li>
<li>Experimentalphysik I - III, Bechinger, WS09, SS10  
 <br>Dressel, WS10: <a href=./files/exphys>exphys</a></li>
<li>Grundlagen der Informatik, Roller, WS09: <a href=./files/info>info</a></li>
<li>Lineare Algebra und Analytische Geometrie, K&uuml;hnel, WS09, SS10: <a href=./files/laag>laag</a></li>
<li>Mathematische Methoden der Physik, B&uuml;chler, WS09: <a href=./files/mmp>mmp</a></li>
<li>Theoretische Physik I - II, B&uuml;chler, SS09, WS10: <a href=./files/thph1>thph1</a></li>
<li>Spezielle Relativit&auml;tstheorie, Wessel, WS10: <a href=./files/srt>srt</a>
<li>Differenzialgeometrie, Teufel, WS10: <a href=./files/diffgeo>diffgeo</a></li>
</ul>
-->



<p>Wer die alte Ansicht kennen und lieben gelernt hat, kann sie hier noch finden: <a href=./files_alt.php>alt</a>. Diese wird aber <i>nicht mehr aktualisiert</i>!





<h3>Motivation f&uuml;r das neue System</h3>


<p>Fr&uuml;her hab ich mal f&uuml;r jede einzelne Datei von Hand einen Eintrag hier gemacht, mit dem Effekt, dass hier auf einer Seite zwar alles da war, daf&uuml;r aber un&uuml;bersichtlich und man hat nicht gesehen, wann die Seite / die Dateien aktualisiert wurden.<p>

<p>Wenn ich mich vertippt habe, war die Datei einfach nicht auffindbar. Und zu guter Letzt spare ich so Zeit ;-)</p>








</div>
  
  
  
  
  </body>
</html>
