'''
  Author : Aravind
  Wbsite : https://www.jestronics.ml/
  Developed on : 03/09/2022
  IDE : Python
  Version : 3.9
  Supported platform : AWS Lamnbda/local AWS setup
'''
import json
import boto3
import os

dynamo_client  =  boto3.resource(service_name = 'dynamodb',region_name = 'us-east-1',
              aws_access_key_id = os.environ['AWSAccessKeyId'],
              aws_secret_access_key = os.environ['AWSSecretKey'])

def lambda_handler(event, context): #event triggered from IoT rules
    print(event)
    table = dynamo_client.Table('DeviceConnectivity')

    response = table.put_item(
    Item = { 
         'ClientID': event["clientId"],
         'Connectivity': event["eventType"]
           }
    )
        
    return {
        'statusCode': 200,
        'body': json.dumps('Updated')
    }