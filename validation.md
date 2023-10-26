# Validations on the chain

## Objects
+ Person: ID TAJ NAME BirthDate
+ Health examination: TAJ Sistole Diastole DATE
+ Life insurance: ID TAJ FROM_date TO_date COST PAYMENT_upon_death SHOULD_PAY
+ Work Permit: ID NAME FROM_date

## Events(write funtions):
+ Person: Born, Die
+ Health examination: Issue
+ Life Insurance: Issue
+ Work Permit: Issue, Revoke

## Validations:
+ ALL: Peer has write access
+ Born: Valid data
+ Die: Exsisting person, date is not in future: If person dies and healthInsurance, should pay
+ HealthExaminationIssue: Existing living person, sis dis in range, date in past
+ IssueLifeInsurance: Existing living person, Existing health exam in 6 months, sis dis in range, from_date is future, to_date is future++
+ Issueworkpermit: existing living person, not existing work permit, existing life insurance

