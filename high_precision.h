#include <iostream>
#ifndef HIGH_PRECISION_H_
#define HIGH_PRECISION_H_
namespace std
{
	struct High_precision
	{
		string str;
		High_precision()
		{
			this->str="0";
		}
		High_precision(const string a)
		{
			this->str=a;
		}
		High_precision(const char * a)
		{
			this->str=a;
		}
		High_precision(const long long a)
		{
			string ans="";
			long long aa=a;
			while(aa>=1)
			{
				ans=(char)('0'+aa%10)+ans;
				aa/=10;
			}
			this->str=ans;
		}
		operator string ()
		{
			return this->str;
		}
		operator long long ()
		{
			string str1=this->str;
			long long ans=0;
			for(int i=0;i<str1.length();i++)
				ans=ans*10+(str1[i]-'0');
			long long ret=ans;
			return ret;
		}
		High_precision & operator = (const char * b)
		{
			this->str=b;
			return *this;
		}
		High_precision & operator = (const string b)
		{
			this->str=b;
			return *this;
		}
		High_precision & operator = (const long long a)
		{
			long long aa=a;
			this->str="";
			while(aa>=1)
			{
				this->str=(char)('0'+aa%10)+this->str;
				aa/=10;
			}
			return *this;
		}
	};
	ostream & operator << (ostream & os,const High_precision & a)
	{
		os<<a.str;
		return os;
	}
	istream & operator >> (istream & is,High_precision & a)
	{
		is>>a.str;
		return is;
	}
	bool operator == (const High_precision & a,const High_precision & b)
	{
		string str1=a.str,str2=b.str;
		return str1==str2;
	}
	bool operator < (const High_precision & a,const High_precision & b)
	{
		string str1=a.str,str2=b.str;
		if(str1.length()!=str2.length())
			return str1.length()<str2.length();
		else
			return str1<str2;
	}
	bool operator > (const High_precision & a,const High_precision & b)
	{
		string str1=a.str,str2=b.str;
		if(str1.length()!=str2.length())
			return str1.length()>str2.length();
		else
			return str1>str2;
	}
	bool operator <= (const High_precision & a,const High_precision & b)
	{
		string str1=a.str,str2=b.str;
		if(str1.length()!=str2.length())
			return str1.length()<=str2.length();
		else
			return str1<=str2;
	}
	bool operator >= (const High_precision & a,const High_precision & b)
	{
		string str1=a.str,str2=b.str;
		if(str1.length()!=str2.length())
			return str1.length()>=str2.length();
		else
			return str1>=str2;
	}
	const High_precision operator + (const High_precision & a,const High_precision & b)
	{
		string str1=a.str,str2=b.str;
		int len1=str1.length(),len2=str2.length();
		string ans="";
		if(len1<len2)
		{
			for(int i=1;i<=len2-len1;i++)
				str1='0'+str1;
			len1=len2;
		}
		else
		{
			for(int i=1;i<=len1-len2;i++)
				str2='0'+str2;
			len2=len1;
		}
		char j=0,temp;
		for(int i=max(len1,len2)-1;i>=0;i--)
		{
			temp=(len1>i?str1[i]-'0':0)+(len2>i?str2[i]-'0':0)+j;
			j=temp/10;
			ans=(char)('0'+temp%10)+ans;
		}
		const High_precision ret=(High_precision){ans};
		return ret;
	}
	const High_precision operator - (const High_precision & a,const High_precision & b)
	{
		string str1=a.str,str2=b.str;
		int len1=str1.length(),len2=str2.length();
		string ans="";
		char j=0,temp;
		for(int i=max(len1,len2)-1;i>=0;i--)
		{
			temp=(len1>i?str1[i]-'0':0)-(len2>i?str2[i]-'0':0)-j;
			if(temp<0)
			{
				j=(0-temp)/10+((0-temp)%10!=0);
				temp+=j*10;
			}
			ans=(char)('0'+temp%10)+ans;
		}
		while(ans[0]=='0'&&ans.length()>=2)
			ans.erase(ans.begin());
		const High_precision ret=(High_precision){ans};
		return ret;
	}
	const High_precision operator * (const High_precision & a,const High_precision & b)
	{
		string str1=a.str,str2=b.str;
		int len1=str1.length(),len2=str2.length();
		string ans="";
		char temp;
		for(int i=0;i<len1;i++)
		{
			for(int j=0;j<len2;j++)
			{
				temp=(str1[i]-'0')*(str2[j]-'0');
				if(i+j>=ans.length())
					for(int k=ans.length();k<=i+j;k++)
						ans+='0';
				for(int k=i+j;k>=0&&ans[k]+j<='9';k--)
				{
					temp=(ans[k]-'0')+temp;
					ans[k]=(char)('0'+temp%10);
					temp/=10;
				}
				if(temp>=1)
					ans=(char)('0'+temp)+ans;
			}
		}
		const High_precision ret=(High_precision){ans};
		return ret;
	}
	const High_precision operator / (const High_precision & a,const High_precision & b)
	{
		string str1=a.str,str2=b.str;
		int len1=str1.length(),len2=str2.length();
		string ans="";
		if(len2>len1)
			ans="0";
		else
			for(int i=0;i+len2-1<len1;i++)//str1[i~i+len2-1]       str2[0~len2-1]
			{
				int l=0,r=9,cheng=0;
				string jian;
				while(l<=r)
				{
					int mid=(l+r)/2;
					string product="";
					int j=0,temp;
					for(int w=len2-1;w>=0;w--)
					{
						temp=(str2[w]-'0')*mid+j;
						j=temp/10;
						product=(char)('0'+temp%10)+product;
					}
					if(j>=1)
					{
						r=mid-1;
						continue;
					}
					string str=str1.substr(i,len2);
					if(product==str)
					{
						jian=product;
						cheng=mid;
						break;
					}
					else if(product<str)
					{
						jian=product;
						cheng=mid;
						l=mid+1;
					}
					else
						r=mid-1;
				}
				ans+=(char)('0'+cheng);
				int j=0,temp;
				for(int w=len2-1;w>=0;w--)
				{
					temp=(str1[i+w]-'0')-(jian[w]-'0')-j;
					if(temp<0)
					{
						j=(0-temp)/10+((0-temp)%10!=0);
						temp+=j*10;
					}
					str1[i+w]=temp;
				}
			}
		const High_precision ret=(High_precision){ans};
		return ret;
	}
}
#endif
