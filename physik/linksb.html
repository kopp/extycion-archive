<html>
<head>
<title>Physiker-Blog: Links</title>
<meta name=Author content="Michael Kopp">
<link rel=stylesheet tpye=text/css href=style.css>
</head>

<?php
$xml_filename = "physlinks01.xml";
$dieses_dokument = "linksb.php";
?>

<?php
//Verbindung herstellen
$links_xml = simplexml_load_file("$xml_filename");
?>


<?php

// Neue Links eintragen

if($_POST["new_verbindung_submit"]){	//"Link eintragen" Taste wurde gedrueckt
	// Eingeragene Werte auslesen
	$adresse = $_POST["new_verbindung_adresse"];
	$beschreibung = $_POST["new_verbindung_beschreibung"];
	$name = $_POST["new_verbindung_name"];
	$zeitstempel = (string) time();

	if(empty($adresse)){
		echo '<span style="color: red">Bitte eine Adresse eingeben!</span>';
		break;
	}

	if(empty($beschreibung)){
		echo '<span style="color: red">Bitte eine Beschreibung eingeben!</span>';
		break;
	}


	// FOrmatieren: Wenn adresse kein http enthält, ein solches hinzufügen
	if(strcasecmp($adresse, "http://") != 0){ //$adresse enthält kein http
		$adresse = "http://".$adresse;
	}


	$kommentar_anhang = '<form method=post action='.$dieses_dokument.'><input type=hidden name=zeitstempel value='.$zeitstempel.'>Kommentartext: <input type=text size=20 name=kommentartext> Name: <input type=text size=08 name=kommentator><input type=submit name=kommentar_hinzufuegen value=kommentieren></form>';


	if(!(empty($name))){
		$beschreibungstext = $beschreibung." (bereitgestellt von ".$name.")";
	}
	else{
		$beschreibungstext = $beschreibung;
		$name = "Anonym";
	}

	//$beschreibungstext .= $kommentar_anhang;




	$new_verbindung = $links_xml->addChild('verbindung'); //erzeugt ein neues <verbindung>
	$new_verbindung->addChild("adresse",$adresse);
	$new_verbindung->addChild("name",$name);
	$new_verbindung->addChild("beschreibung", $beschreibung);
	//$new_verbindung->addChild("beschreibungstext", $beschreibungstext);
	$new_verbindung->addChild("kommentar_anhang", $kommentar_anhang);
	$new_verbindung->addChild("zeitstempel", $zeitstempel);

	$links_xml->asXML($xml_filename);
}

?>





<?php

if($_POST["kommentar_hinzufuegen"]){
	foreach($links_xml->verbindung as $link){
		if($link->zeitstempel == $_POST["zeitstempel"]){	//Passender verbindungseintrag gefunden

			$new_kommentar = $link->addChild("kommentar");
			$new_kommentar->addChild("kommentator", $_POST["kommentator"]);
			$new_kommentar->addChild("kommentartext", $_POST["kommentartext"]);
		}
	}
	$links_xml->asXML($xml_filename);
}

?>





<body>


<div id=navi>
<?php
include("navi.incl");
?>
</div>



<div id=inhalt>


<h1 id=seitentitel>Links (B)</h1>



<h2>Vorab</h2>

<p>Dies ist eine erweiterbare Linkliste. Wer denkt, er wei&szlig; einen tollen Link, der ist herzlich dazu aufgerufen, ganz unten (<a href=#kap_link_hinzufuegen>link</a>) diesen einzutragen.  
Ebenso kann man die bereits eingetragenen Links kommentieren.</p>

<p>Diese Seite befindet sich noch im Aufbau -- trotzdem k&ouml;nnen manche features schon verwendet werden. Die bereits online gestellten Sachen werden mit der Zeit noch verbessert.</p>

<p><span id=alert>Wichtig</span>: Wenn man hier eintragen will, sollte man  <span id=emp>keine</span> Sonderzeichen verwendet -- die Volle Zeichenunterst&uuml;tzung kommt auch noch... bald....</p>





<h2>Allgemeine Links</h2>



<?php
//anzeige
echo "<ol>";
foreach($links_xml->verbindung as $link){
	echo "<li class=linkliste><a class=linkliste href='";
	echo $link->adresse;
	echo "'>";
	echo $link->adresse;
	echo "</a> -- ";
	echo $link->beschreibung;
	if($link->name != "Anonym"){
		echo " <span class=linkliste id=link_name>(bereitgestellt von ";
		echo $link->name;
		echo ")</span>";
	}
	echo "</li>\n";
	if($link->kommentar){
		echo "<ul>";
		foreach($link->kommentar as $kommentar){
			echo "<li>";
			echo $kommentar->kommentartext;
			echo " -- von ";
			echo $kommentar->kommentator;
			echo "</li>";
		}
		echo "</ul>";
	}
	echo $link->kommentar_anhang;
}
echo "</ol>";

?>










<h2 name=kap_link_hinzufuegen>Link hinzuf&uuml;gen</h2>
<form name=new_verbindung method=post action="<?php echo $dieses_dokument; ?>">
<table border=0>
<tr><td>Web-Adresse:</td><td><input type=text size=20 name=new_verbindung_adresse></td></tr>
<tr><td>Beschreibung der Seite:</td><td><input type=text size=20 name=new_verbindung_beschreibung></td></tr>
<tr><td>Dein Name:</td><td><input type=text size=20 name=new_verbindung_name></td></tr>
<tr><td><input type=submit name=new_verbindung_submit></td><td></td></tr>
</table>
</form>





</div>


</body>
