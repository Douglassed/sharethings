#!/bin/sh
jour="`date -R | cut -f1 -d','`"
case $jour in
  Mon )
    jour="Lundi"
    ;;
  Tue )
    jour="Mardi"
    ;;
  Wed )
    jour="Mercredi"
    ;;
  Thu )
    jour="Jeudi"
    ;;
  Fri )
    jour="Vendredi"
    ;;
  Sat )
    jour="Samedi"
    ;;
  Sun )
    jour="Dimanche"
    ;;
esac

mois="`date -R | cut -f3 -d' '`"
case $mois in
  Jan )
    mois="Janvier"
    ;;
  Feb )
    mois="Fevrier"
    ;;
  Mar )
    mois="Mars"
    ;;
  Apr )
    mois="Avril"
    ;;
  May )
    mois="Mai"
    ;;
  Jun )
    mois="Juin"
    ;;
  Jul )
    mois="Juillet"
    ;;
  Aug )
    mois="Aout"
    ;;
  Sep )
    mois="Septembre"
    ;;
  Oct )
    mois="Octobre"
    ;;
  Nov )
    mois="Novembre"
    ;;
  Dec )
    mois="Decembre"
    ;;
esac

echo "$jour `date -R | cut -f2 -d' '` $mois `date -R | cut -f4 -d' '` `date -R | cut -f5 -d' '`" > "./Tempo.txt"
exit 0
