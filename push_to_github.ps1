# LesFight - GitHub Push Script
# Run this script in PowerShell (Right-click → Run with PowerShell)

Write-Host "=== Pushing LesFight to GitHub ===" -ForegroundColor Green

# Navigate to project
Set-Location "H:\Lesfight"

# Initialize git if not already done
if (-not (Test-Path ".git")) {
    git init
    Write-Host "Git initialized" -ForegroundColor Yellow
}

# Add safe directory exception for this drive
git config --global --add safe.directory "H:/LesFight" 2>$null

# Add all files
git add -A

# Show status
git status

# Commit
$commitMsg = "LesFight - Initial commit - Unreal Engine 5.4 fighting game"
git commit -m $commitMsg

# Add remote
$remoteUrl = "https://github.com/mahuvechriss/Lesfight.git"
git remote remove origin 2>$null
git remote add origin $remoteUrl
Write-Host "Remote set to: $remoteUrl" -ForegroundColor Yellow

# Push to GitHub
Write-Host "Pushing to GitHub... (you may be prompted to log in)" -ForegroundColor Green
git push -u origin main

Write-Host "=== Done! ===" -ForegroundColor Green
