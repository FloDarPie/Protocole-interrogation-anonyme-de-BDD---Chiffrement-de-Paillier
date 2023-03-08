___
# <center> Chiffrement de Pailler 
#### <center> *Protocole d’interrogation anonyme de base de données*
### <center> TER 2023

<br>
<br>
<p align="justify"> D’ordinaire, pour récupérer un champ d’une base de données, un client envoie une requête indiquant quel élément l’intéresse, puis la base lui renvoie cet élément. Quel élément a été consulté est une information que le client peut ne pas souhaiter divulguer y compris au serveur de base de données.
Pour protéger l’anonymat de la requête, des protocoles, appelés protocoles PIR (Private Information Retrieval) ont été proposés. Il s’agira d’étudier et de mettre en œuvre une construction de protocole PIR utilisant des systèmes de chiffrement dits homomorphes additifs, comme le système de Paillier.
<br>
<br>
<br>

<p align="justify"> 
Le cryptosystème de Paillier a été créé en 1999 par Pascal Paillier. Il s'agit également d'un chiffrement asymétrique. Il est homomorphe pour l'addition, c'est pourquoi il peut être utilisé dans le cadre du vote électronique. 
<br>
Un cryptosystème est un terme utilisé en cryptographie pour désigner un ensemble composé d'algorithmes cryptographiques et de tous les textes en clair, textes chiffrés et clés possibles (définition de Bruce Schneier).
<br>
<br>
Un système cryptographique est un ensemble d’algorithmes cryptographiques nécessaires à la mise en œuvre d’un service de sécurité particulier tel que le cryptage. Ce terme est une combinaison d’un système cryptographique (c’est-à-dire un système informatique qui utilise un mot de passe). Un système cryptographique est une méthode de protection des informations et de communication par codes, de sorte que seuls les utilisateurs confrontés à l’information puissent lire celle-ci. Les composants de base d’un système cryptographique sont les suivants :
<br>
    - **Texte en clair**: données qui doivent être protégées pendant la transmission.
    Algorithme de chiffrement: processus mathématique qui utilise un algorithme pour transformer des informations en un texte chiffré dénué de sens et qui nécessite l’utilisation d’une clé pour retransformer les données dans leur forme originale.<br>
    - **Ciphertext**: la version chiffrée du texte en clair qui a été produite par un algorithme de chiffrement utilisant une clé de chiffrement spécifique.<br>
    - **Algorithme de décryptage**: Processus mathématique qui produit un texte en clair pour un texte chiffré et une clé de décryptage donnés. Le texte chiffré et la clé de décryptage sont l’entrée, le texte en clair est la sortie.<br>
    - **Clé de chiffrement**: Valeur connue de l’expéditeur. L’expéditeur entre la clé de chiffrement dans l’algorithme de chiffrement avec le texte en clair pour calculer le texte chiffré.<br>
    - ** Clé de décryptage **: Valeur connue du récepteur. Le récepteur entre la clé de déchiffrement dans l’algorithme de déchiffrement avec le texte chiffré pour calculer le texte en clair.
<br>
Les cryptosystèmes sont utilisés pour l’envoi sécurisé de messages sur l’internet, tels que des informations sur les cartes de crédit ou toute autre donnée qui doit rester privée. Un intercepteur est une entité non autorisée qui tente de déterminer le texte en clair.<br>
Types de cryptosystèmes<br>

Il existe deux types de cryptosystèmes, qui sont classés en fonction de la méthode utilisée pour chiffrer les données :
<br>
 - **Cryptage à clé symétrique**: système de cryptage dans lequel l’expéditeur et le destinataire d’un message partagent une clé publique unique qui est utilisée pour crypter et décrypter le message.<br>
 - **Cryptage à clé asymétrique**: système de cryptage dans lequel des clés différentes sont utilisées pour le cryptage et le décryptage, les clés étant mathématiquement liées. Chaque partie possède sa propre paire de clés qui est échangée pendant la transmission.
<br>
<br>
<br>
<br>
<br>
<br>



<u> Source :</u><br>
 - Un <a href=https://github.com/mikeivanov/paillier>code python.</a><br>
 - Pascal Paillier, Public Key Cryptosystems based on Composite Degree Residue Classes, <a href=https://www.lamsade.dauphine.fr/~litwin/cours98/Doc-cours-clouds/Pai99pai.pdf>référence.</a>



