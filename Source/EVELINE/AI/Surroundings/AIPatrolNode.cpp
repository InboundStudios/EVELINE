// Fill out your copyright notice in the Description page of Project Settings.

#include "AIPatrolNode.h"



AAIPatrolNode::AAIPatrolNode()
{
	bIsOccupied = false;
}

void AAIPatrolNode::SetOccupyStatus(bool NewStatus)
{
	bIsOccupied = NewStatus;
}


